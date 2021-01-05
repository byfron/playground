set(SOURCES
  imconfig.h
  imgui.cpp
  imgui.h
  imgui_demo.cpp
  imgui_draw.cpp
  imgui_internal.h
  imgui_widgets.cpp
  imstb_rectpack.h
  imstb_textedit.h
  imstb_truetype.h
  imgui_impl_glfw.cpp
  imgui_impl_glfw.h
  imgui_impl_opengl3.cpp
  imgui_impl_opengl3.h
  gl3w/GL/gl3w.c
  )

add_library(LIBIMGUI ${SOURCES})  
target_link_libraries(LIBIMGUI ${SDL2_LIBRARIES} GL dl)
target_include_directories(LIBIMGUI PRIVATE ${SDL2_INCLUDE_DIRS})  
  
