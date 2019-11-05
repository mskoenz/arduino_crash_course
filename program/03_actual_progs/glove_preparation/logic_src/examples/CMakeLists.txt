FOREACH (name   test_logic
    )
    add_executable(${name} ${name}.cpp)
    add_dependencies(${name} logic)
    target_link_libraries(${name} logic)
ENDFOREACH(name)
