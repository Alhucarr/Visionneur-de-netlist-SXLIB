# -*- explicit-buffer-name: "CMakeLists.txt<M1-MOBJ/7>" -*-
#
# To display executed commands, use:
#     > cmake -DCMAKE_VERBOSE_MAKEFILE:STRING=YES ../src

 cmake_minimum_required(VERSION 2.8.0)
 project(SCHEMATIC)
 
 set (CMAKE_CXX_FLAGS            "-Wall -g" CACHE STRING "C++ Compiler Release options." FORCE)
 set (CMAKE_INSTALL_PREFIX       "../install" )

# Detection de LibXml2.
   find_package(LibXml2)

# Trouver les includes de LibXml2.
   include_directories( ${SCHEMATIC_SOURCE_DIR} ${LIBXML2_INCLUDE_DIR} )


   include_directories( ${SCHEMATIC_SOURCE_DIR}
                       )

                    set( includes     Indentation.h
                                      Term.h
                                      Net.h
                                      Instance.h
                                      Point.h
                                      Node.h
                                      Symbol.h
                                      Line.h
                                      Box.h
                                      Cell.h
                                      XmlUtil.h
                                      shape.h
                       )

                    set( cpps         Indentation.cpp
                                      Term.cpp
                                      Box.cpp
                                      Net.cpp
                                      Instance.cpp
                                      Point.cpp
                                      Line.cpp
                                      Node.cpp
                                      Cell.cpp
                                      Symbol.cpp
                                      Shape.cpp
                                      TermShape.cpp
                                      BoxShape.cpp
                                      LineShape.cpp
                                      ArcShape.cpp
                                      EllipseShape.cpp
                                      XmlUtil.cpp
                                      Main.cpp
                       )
# Faire l'edition de liens avec la LibXml2.
   add_executable ( tme7 ${cpps} )
   target_link_libraries ( tme7 ${LIBXML2_LIBRARIES} )
               install ( TARGETS      tme7         DESTINATION bin )
               install ( FILES        ${includes}  DESTINATION include )
