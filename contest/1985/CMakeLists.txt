get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
foreach(problem a b c d e f g h1 h2)
  add_executable(${DIR}_${problem} ${problem}/main.cc)
endforeach(problem)
