add_project_link_arguments([
  '-lcuda', 
  '-lopencv_core', 
  '-lopencv_highgui', 
  '-lopencv_imgproc', 
  '-lopencv_imgcodecs'
], language: 'cpp')

clink_deps += [
  dependency('uuid')
]

clink_include += [
  '/usr/local/cuda-12.1/targets/x86_64-linux/include/',
  '/usr/include/opencv4'
]

clink_sources += files(
  'cuda.cc',
)
