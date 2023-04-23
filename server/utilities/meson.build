add_project_link_arguments([
  '-lopencv_core', 
  '-lopencv_highgui', 
  '-lopencv_imgproc', 
  '-lopencv_imgcodecs'
], language: 'cpp')

clink_sources += files(
  'image.cc',
  'logger.cc',
  'zstd.cc',
)

clink_include += [
  '/usr/include/opencv4'
]

clink_deps += dependency('libzstd')
