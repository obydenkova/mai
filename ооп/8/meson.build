project('oop_exercise_08', 'cpp')

add_project_arguments('-std=c++17', '-w', '-pthread', language : 'cpp')

thread_dep = dependency('threads')

executable(
    meson.project_name(),
    'main.cpp',
    'factory.cpp',
    'point.cpp',
    'processor.cpp',
    'rectangle.cpp',
    'square.cpp',
    'subscriber.cpp',
    'trapezoid.cpp',
    dependencies : thread_dep
)
