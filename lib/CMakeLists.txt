cmake_minimum_required(VERSION 3.0.0)

# bbclib serves as the core library of bbc
add_library(bbclib
            account.cpp account.h
            date.cpp date.h
            group_mode.cpp group_mode.h
            member.cpp member.h
            person_mode.cpp person_mode.h
            profile.cpp profile.h
            screen_util.cpp screen_util.h)

install(TARGETS bbclib DESTINATION lib)
install(FILES account.h 
              date.h
              group_mode.h
              member.h
              person_mode.h
              profile.h
              screen_util.h
              DESTINATION include
              )
