# better way ?
INCLUDE_DIRECTORIES(.)

# Source files
# ====================================
#           (Glob is not recommended)

SET(PROJECT_TEST_HDS
    Scene.h
    Drawable.h
    Vector.h
    Sphere.h
    Color.h
    Ray.h
    Light.h
    Camera.h
    Render.h
    ARender.h
    Image.h
    PaintDevice.h
)

SET(PROJECT_TEST_SRC
    Scene.cpp
    Drawable.cpp
    Sphere.cpp
)

# main library (prevent recompilation when building tests)
ADD_LIBRARY(${PROJECT_NAME} ${PROJECT_TEST_SRC} ${PROJECT_TEST_HDS})
SET_PROPERTY(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)


#  main executable
# ==========================

ADD_EXECUTABLE(main main.cpp)
TARGET_LINK_LIBRARIES(main raytracing)
SET_PROPERTY(TARGET main PROPERTY CXX_STANDARD 14)



