util_sources = [
  'util_func.cpp',
  'profiler.cpp',
  'ini_wrapper.cpp',
  'node_exporter.cpp',
  'base_properties.cpp',
  'nntr_threads.cpp',
  'fp16.cpp',
  'util_simd.cpp',
  'mman_windows.cpp',
  'bs_thread_pool_manager.cpp'
]

util_headers = [
  'base_properties.h',
  'node_exporter.h',
  'util_func.h',
  'profiler.h',
  'nntr_threads.h',
  'fp16.h',
  'util_simd.h',
  'dynamic_library_loader.h',
  'mman_windows.h',
  'bs_thread_pool.h',
  'bs_thread_pool_manager.hpp',
]

if get_option('enable-trace')
  util_sources += 'tracer.cpp'
  util_headers += 'tracer.h'
endif

if get_option('enable-fp16')
  util_sources += 'util_simd_fp16.cpp'
endif

foreach s : util_sources
  nntrainer_sources += meson.current_source_dir() / s
endforeach

foreach h : util_headers
  nntrainer_headers += meson.current_source_dir() / h
endforeach
