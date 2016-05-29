# better way ?
INCLUDE_DIRECTORIES(.)

# Source files
# ====================================
#           (Glob is not recommended)

SET(PROJECT_TEST_HDS
    #symbolic.h
)

SET(PROJECT_TEST_SRC
    main.cpp
)

# main library (prevent recompilation when building tests)
ADD_LIBRARY(${PROJECT_NAME} ${PROJECT_TEST_SRC} ${PROJECT_TEST_HDS})
SET_PROPERTY(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)


#  main executable
# ==========================

# ADD_EXECUTABLE(main main.cpp)
# TARGET_LINK_LIBRARIES(main project_test)
# SET_PROPERTY(TARGET main PROPERTY CXX_STANDARD 11)



