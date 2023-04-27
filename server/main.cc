/* 
 * Clink
 * Copyright (C) 2023 cair <rui.cai@tenclass.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <cuda.h>
#include <stdio.h>
#include <signal.h>
#include <getopt.h>

#include "server.h"
#include "logger.h"
#include "version.h"

static Server* server = nullptr;

static void PrintHelp() {
  printf("Usage: clink [option]\n");
  printf("Options\n");
  printf("  -h, --help            Display this information.\n");
  printf("  -v, --version         Display clink version information.\n");
  printf("  -u, --uuid            Specified clink uuid information.\n");
  printf("  -p, --port            Specified clink port information.\n");
  printf("  -n, --net             Specified network information, tcp or kcp.\n");
}

static void PrintVersion() {
  printf("CLink: %s\n", VERSION);
  printf("Copyright (C) 2023 cair <rui.cai@tenclass.com>.\n");
  printf("License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n");
  printf("This is free software: you are free to change and redistribute it.\n");
  printf("There is NO WARRANTY, to the extent permitted by law\n");
}

static struct option long_options[] = {
  {"help", no_argument, 0, 'h'},
  {"version", no_argument, 0, 'v'},
  {"uuid", required_argument, 0, 'u'},
  {"port", required_argument, 0, 'p'},
  {"net", required_argument, 0, 'n'},
  {NULL, 0, 0, 0}
};

int main(int argc, char* argv[])  {
  std::string uuid_string;
  std::string port_string;
  std::string net_string;

  int c, option_index = 0;
  while ((c = getopt_long_only(argc, argv, "hvu:p:", long_options, &option_index)) != -1) {
    switch (c) {
      case 'h':
        PrintHelp();
        return 0;
      case 'v':
        PrintVersion();
        return 0;
      case 'u':
        uuid_string = optarg;
        break;
      case 'p':
        port_string = optarg;
        break;
      case 'n':
        net_string = optarg;
        break;
    }
  }

  if (uuid_string.empty() || port_string.empty()) {
    CL_ERROR("invalid args");
    return -1;
  }

  uuid_t uuid;
  auto ret = uuid_parse(uuid_string.c_str(), uuid);
  if (ret != 0) {
    CL_ERROR("uuid parse error=%d uuid_string=%s", ret, uuid_string.c_str());
    return -2;
  }

  NetworkProtocol net;
  if (net_string == "tcp") {
    net = tcp;
  } else if (net_string == "kcp"){
    net = kcp;
  } else {
    CL_ERROR("unknown net type");
    return -3;
  }

  server = new Server(atoi(port_string.c_str()), uuid);
  auto quit_callback = [](int signum) {
    CL_UNUSED(signum);
    server->Quit();
  };
  signal(SIGINT, quit_callback);
  signal(SIGTERM, quit_callback);

  server->Run(net);
  delete server;

  return 0;
}