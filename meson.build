project('strgen', 'cpp', version: '0.0.1', default_options: ['cpp_std=c++20'])

incdirs = include_directories('include')
sources = [
    'src/nodes.cpp',
    'src/parser.cpp',
    'src/stringgenerator.cpp',
]

strgen = static_library('strgen', sources, include_directories : incdirs)

strgen_dep = declare_dependency(
   include_directories : incdirs,
   link_with : strgen,
   sources : sources)