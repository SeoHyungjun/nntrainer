model_util_path = meson.current_source_dir()
model_util_include_dir = include_directories('.')

test_name = 'unittest_models'
mixed_test_name = 'unittest_mixed_models'

test_target = []

models_targets = [
  'models_test_utils.cpp',
  'models_golden_test.cpp',
  'unittest_models_recurrent.cpp',
  'unittest_models_multiout.cpp',
  'unittest_models.cpp',
  # disable temperally
]

mixed_test_targets = [
  'models_test_utils.cpp',
  'models_golden_test.cpp',
  'unittest_models_mixed_precision.cpp',
]

if get_option('enable-fp16')
  mixed_exe = executable(
    mixed_test_name,
    mixed_test_targets,
    include_directories: include_directories('.'),
    dependencies: [
      nntrainer_test_main_deps, nntrainer_ccapi_dep
    ],
    install: get_option('enable-test'),
    install_dir: application_install_dir
  )

  test(mixed_test_name, mixed_exe,
    args: '--gtest_output=xml:@0@/@1@.xml'.format(meson.build_root(), mixed_test_name),
    timeout: test_timeout,
    suite: 'unittests'
  )
endif

test_target += models_targets
exe = executable(
  test_name,
  test_target,
  include_directories: include_directories('.'),
  dependencies: [
    nntrainer_test_main_deps, nntrainer_ccapi_dep
  ],
  install: get_option('enable-test'),
  install_dir: application_install_dir
)

test(test_name, exe,
  args: '--gtest_output=xml:@0@/@1@.xml'.format(meson.build_root(), test_name),
  timeout: test_timeout,
  suite: 'unittests'
)
