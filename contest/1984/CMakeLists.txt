get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
foreach(problem a b c1 c2 d e f g h)
  add_executable(${DIR}_${problem} ${problem}/main.cc)
endforeach(problem)
