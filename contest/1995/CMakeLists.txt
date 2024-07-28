get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
foreach(problem a b1 b2 c d e1 e2)
  add_executable(${DIR}_${problem} ${problem}/main.cc)
endforeach(problem)
