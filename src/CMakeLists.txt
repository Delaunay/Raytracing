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
    Debug.h
    Utils.h
)

SET(PROJECT_TEST_SRC
    Scene.cpp
    Drawable.cpp
    Sphere.cpp
)

SET(PHOTON_MAP_SRC
    ../dependencies/PhotonMap.cpp
    ../dependencies/PhotonMap.h
)

# main library (prevent recompilation when building tests)
ADD_LIBRARY(${PROJECT_NAME} ${PROJECT_TEST_SRC} ${PROJECT_TEST_HDS} ${PHOTON_MAP_SRC})
SET_PROPERTY(TARGET ${PROJECT_NAME} APPEND PROPERTY CXX_STANDARD 14)
SET_PROPERTY(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_FLAG -fopenmp)

#  main executable
# ==========================

ADD_EXECUTABLE(main main.cpp)
TARGET_LINK_LIBRARIES(main raytracing -fopenmp)
SET_PROPERTY(TARGET main APPEND PROPERTY CXX_STANDARD 14)
SET_PROPERTY(TARGET main APPEND PROPERTY COMPILE_FLAG -fopenmp)


