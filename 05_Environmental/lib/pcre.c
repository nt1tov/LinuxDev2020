#ifndef PCRE2_CODE_UNIT_WIDTH
#define PCRE2_CODE_UNIT_WIDTH 8
#endif

#include <stdio.h>
#include <string.h>
#include <pcre2.h>
#include "pcre.h"

#define MAXSTR 80

char* check_pattern(const char* patrn_str, const char* subj_str)
{
	char buff[MAXSTR];
	int mem_shift = snprintf(buff, MAXSTR, "%s: %s\n", patrn_str, subj_str);
	char *res = malloc(sizeof(char) * (MAXSTR + mem_shift + 1)); 
	strncpy(res, buff, mem_shift);
	
	pcre2_code *re;
    PCRE2_SPTR pattern;/* PCRE2_SPTR is a pointer to unsigned code units of */
    PCRE2_SPTR subject; /* the appropriate width (in this case, 8 bits). */

    int errnum;
    int i, rc;

    PCRE2_SIZE erroffs;
    PCRE2_SIZE *ovector;
    PCRE2_SIZE subject_length;

    pcre2_match_data *match_data;

    pattern = (PCRE2_SPTR) patrn_str;
    subject = (PCRE2_SPTR) subj_str;
    subject_length = (PCRE2_SIZE)strlen((char *)subject);

#ifdef WITHOUT_UTF
    re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, 0, &errnum, &erroffs, NULL);
#else
    re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, PCRE2_UCP, &errnum, &erroffs, NULL);
#endif

    if (re == NULL) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(errnum, buffer, sizeof(buffer));
        
		sprintf(res+mem_shift, MAXSTR, "PCRE2 compilation failed at offset %d: %s\n", (int)erroffs,
               buffer);
        return res;
    }

    match_data = pcre2_match_data_create_from_pattern(re, NULL);

    rc = pcre2_match(re, subject, subject_length, 0, 0, match_data, NULL);

    if (rc < 0) {
        switch(rc) {
			case PCRE2_ERROR_NOMATCH:
				snprintf(res+mem_shift, MAXSTR, " No match\n");
				break;
			default:
				snprintf(res+mem_shift, MAXSTR, " Matching error %d\n", rc);
				break;
        }
        pcre2_match_data_free(match_data);   /* Release memory used for the match */
        pcre2_code_free(re);                 /*   data and the compiled pattern. */
        return res;
    }

//	printf("ok!\n");
//    return res;
    ovector = pcre2_get_ovector_pointer(match_data);
	

    for (i = 0; i < rc; i++){
        int ms = snprintf(buff, MAXSTR, "%2ld: %.*s\n", ovector[2*i], 
			     (int)(ovector[2*i+1] - ovector[2*i]),
			     subject + ovector[2*i]);
		res = realloc(res, sizeof(char) * (ms + mem_shift + 1));
		strncpy(res+mem_shift, buff, ms);
		mem_shift += ms;

	}
	res[mem_shift] = '\0';

    pcre2_match_data_free(match_data);  /* Release the memory that was used */
    pcre2_code_free(re);                /* for the match data and the pattern. */

    return res;
}

