/*
   Digital Rights Management (DRM) module.
   Microtrans Games Inc.

   Author: Ada Typical, 2019
*/
#include "drm.h"

#include <cstdio>
#include <cstring> 
#include <cstdlib>
#include <ctime>

namespace drm {

// (A.Typical) for now we store the codes here, should move them to a safer place in future
static const code_id MAX_CODES = 3;
static const unsigned int MAX_CODE_LEN = 8;
static const char* queries[] = {"Please enter the second word on page 5 in your handbook."
                                , "Please enter the 10th word on page 10 in your handbook."
                                , "Please enter the 7th word on page 3 in your handbook."};
static const char* codes[] = { "ground", "fork", "powerup" };

code_id get_random_code_id() {
   std::srand(std::time(nullptr));
   return std::rand() % MAX_CODES;
}

/*
  (A.Typical) TODO: this will retrieve the query string from somewhere else,
  consider this implementation temporary
*/
int get_query(code_id id, char* result_query) {
   if (id < MAX_CODES) {
      std::strcpy(result_query, queries[id]);
      return 0;
   }
   return -1;
}

/*
  (A.Typical) TODO: this will retrieve the query string from somewhere else,
  consider this implementation temporary
*/
int get_code(code_id id, char* result_code) {
   if (id < MAX_CODES) {
      std::strcpy(result_code, codes[id]);
      return 0;
   }
   return -1;
}

bool check_code(code_id id, const char* user_code) {
   static char cached_user_code[MAX_CODE_LEN] = "";
   static char cached_real_code[MAX_CODE_LEN] = "";

   // if we don't have the real code cached yet, retrieve it  now
   if (std::strlen(cached_real_code) == 0) {
      if (get_code(id, cached_real_code) != 0) {
         return false;
      }
   }

   // We copy the user code as we would like to use
   // it for further checks later - in case some
   // cracker skips the initial code check
   if (user_code != nullptr) {
      std::strcpy(cached_user_code, user_code);
   }
 
   if (!std::strcmp(cached_real_code, cached_user_code)) {
      return true;
   }
   return false;
}

}