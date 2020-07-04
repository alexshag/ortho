#pragma once

/* all string parsers are placed here */

int parse_waypoints(const char* string, wplist** ppList);
int parse_magvar(const char* string, wplist** ppList);
int parse_pmdg(const char* string, wplist** ppList);
