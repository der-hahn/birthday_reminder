# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/birthday_reminder_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/birthday_reminder_autogen.dir/ParseCache.txt"
  "birthday_reminder_autogen"
  )
endif()
