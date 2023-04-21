# Generate cuda export functions head file and implements cpp file
# from offical source file cuda.h
# Usage: cuda_export_impl_gen.py cuda.h
#
# Copyright (C) 2023 cair <rui.cai@tenclass.com>
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
import re

functions = []
func_names = []
impls = []

cuda_path = "cuda.h"

def extract_function_names(string):
    pattern = r'\b\w+\('
    matches = re.findall(pattern, string)
    return [match[:-1] for match in matches][0]

def extract_c_function_params(c_function_signature):
    pattern = r'\(([^)]*)\)'  # Search for content inside parentheses
    params_str = re.search(pattern, c_function_signature).group(1).strip()
    
    # Return an empty list if no parameters
    if not params_str or params_str.lower() == "void":
        return []

    # Split parameters by comma, then extract parameter names
    params = [param.strip().split(' ')[-1].rstrip('*') for param in params_str.split(',') if param.strip()]
    return params

with open(cuda_path, 'r', encoding='utf-8') as f:
    line = f.readline()
    while line:
        if line.startswith("CUresult CUDAAPI") or line.startswith("__CUDA_DEPRECATED CUresult CUDAAPI") :
            line = line.replace("\n", "").replace("__CUDA_DEPRECATED ", "")
            if line.endswith(";"):
                functions.append(line)
            else:
                while not line.endswith(";"):
                    line += " " + f.readline().replace("\n", "")
                functions.append(line)

        line = f.readline()

index = 0
for func in functions:
    func = func[:-1]

    func_name = extract_function_names(func)
    func_names.append(func_name)

    params = extract_c_function_params(func)

    impl = "return (CUresult)CUDADispatch(" + func_name.upper() + "," + str(len(params))  + ","
    for item in params:
        impl += item.replace("*", "")
        impl += ","
    impl = impl[:-1]
    impl += ");"

    func += "{" + impl + "}"
    impls.append(func)
    index += 1

with open("cuda_define.h", "w", encoding="utf-8") as file:
    for i,name in enumerate(func_names):
        file.write("#define " + name.upper() + " " + str(i) + "\n")

with open("cuda_define_string.h", "w", encoding="utf-8") as file:
    for i,name in enumerate(func_names):
        file.write("case " + name.upper() + ": return \"" + name + "\";\n")

with open("cuda_impl.cpp", "w", encoding="utf-8") as file:
    for line in impls:
        file.write(line + "\n")

with open("cuda_export.h", "w", encoding="utf-8") as file:
    with open(cuda_path, "r", encoding="utf-8") as f:
        line = f.readline()
        while line:
            if line.startswith("CUresult CUDAAPI") or line.startswith("__CUDA_DEPRECATED CUresult CUDAAPI"):
                line = "__declspec(dllexport) " + line
            file.write(line)
            line = f.readline()
