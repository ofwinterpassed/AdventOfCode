project('aoc', 'cpp', default_options : ['cpp_std=c++2a', 'default_library=static'])
compiler = meson.get_compiler('cpp')
if compiler.get_id() == 'gcc'
	add_project_link_arguments('-l:libstdc++.a', language : 'cpp')
endif
executable('part1', 'part1.cpp')
executable('part2', 'part2.cpp', include_directories: '/home/coffee/KingStandardLibrary/kstl/include')
