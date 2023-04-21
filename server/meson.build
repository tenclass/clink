project('clink', 'c', 'cpp',
  version: '1.0.0',
  license: 'GPLv3',
  default_options: [
    'buildtype=debug',
    'warning_level=2',
    'cpp_std=c++17',
    'werror=true'
  ]
)

add_project_arguments('-Wno-error=deprecated-declarations', language: 'cpp')

clink_version_data = configuration_data()
clink_version_data.set_quoted('VERSION', meson.project_version())
configure_file(output: 'version.h',
  configuration: clink_version_data
)

clink_include = [
  include_directories('include'),
]

clink_deps = [
  dependency('threads')
]
clink_sources = []

subdir('utilities')
subdir('render')
subdir('socket')
subdir('server')

clink_sources += ['main.cc']

clink = executable('clink',
  sources: clink_sources,
  include_directories : clink_include,
  dependencies: clink_deps
)