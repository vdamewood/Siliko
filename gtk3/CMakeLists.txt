# CMakeLists.txt: Build Script
# Copyright 2012, 2014, 2015, 2016, 2017, 2018, 2019, 2021 Vincent Damewood
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

find_package(PkgConfig REQUIRED)
pkg_check_modules(Gtk3 REQUIRED gtk+-3.0 IMPORTED_TARGET)

find_program(GRESOURCE glib-compile-resources)
if(NOT GRESOURCE)
	message(FATAL_ERROR "Can't find glib-compile-resources.")
endif()

add_custom_command(
	OUTPUT gresource.h
	COMMAND "${GRESOURCE}"
		--generate-header
		--target=${CMAKE_CURRENT_BINARY_DIR}/gresource.h
		gresource.xml
	DEPENDS gresource.xml
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_command(
	OUTPUT gresource.c
	COMMAND "${GRESOURCE}"
		--generate-source
		--target=${CMAKE_CURRENT_BINARY_DIR}/gresource.c
		gresource.xml
	DEPENDS gresource.xml
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(SilikujoForUnix)
target_sources(SilikujoForUnix
	PRIVATE
		Main.c
		EvalWindow.c
		gresource.c
		EvalWindow.h
		gresource.h
)
set_target_properties(SilikujoForUnix PROPERTIES
	OUTPUT_NAME Silikujo
)
target_compile_features(SilikujoForUnix PRIVATE c_std_11)
target_link_libraries(SilikujoForUnix PRIVATE Siliko::Siliko PkgConfig::Gtk3)

install(TARGETS SilikujoForUnix
	RUNTIME    DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES silikujo.desktop
	DESTINATION "${CMAKE_INSTALL_DATADIR}/applications"
)

install(FILES siliko.png
	DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/48x48/apps"
)
