set(SOURCES
    NeuralOperator.cpp
    PagePredictor.cpp
    WormholeState.cpp
)

set(HEADERS
    Forward.h
    NeuralOperator.h
    PagePredictor.h
    WormholeState.h
)

ladyworm_lib(LibNeural neural SOURCES ${SOURCES} HEADERS ${HEADERS})
target_link_libraries(LibNeural PRIVATE LibCore LibGfx)
