/*
 * x_dep.h
 *
 *  Created on: Dec 13, 2011
 *      Author: myan
 */
#ifndef X_DEP_H_
#define X_DEP_H_

#include "x_type.h"
#include <list>

#define CA_VERSION_MAJOR 2
#define CA_VERSION_MINOR 22
#define CA_VERSION_STRING "2.22"

struct object_reference;
struct reg_value;
struct ca_segment;

struct ca_debug_context
{
    int tid;
    int frame_level;
    address_t sp;
    struct ca_segment* segment;
};

extern bool update_memory_segments_and_heaps(void);

// gdb symbol/value/type
extern bool inferior_memory_read (address_t addr, void* buffer, size_t sz);
extern void ca_switch_to_thread(struct thread_info* info);
extern struct type* ca_type(struct symbol* sym);
extern enum type_code ca_code(struct type* type);
extern const char* ca_name(struct type* type);
extern struct type* ca_field_type(struct type* type, int i);
extern int ca_num_fields(struct type* type);
extern const char* ca_field_name(struct type* type, int i);
extern bool get_gv_value(const char* varname, char* buf, size_t bufsz);
extern bool ca_get_field_value(struct value*, const char*, size_t*, bool);
extern bool ca_memcpy_field_value(struct value*, const char*, char*, size_t);
extern struct value* ca_get_field_gdb_value(struct value*, const char*);

extern void print_register_ref(const struct object_reference* ref);
extern void print_stack_ref(const struct object_reference* ref);
extern void print_global_ref(const struct object_reference* ref);
extern void print_heap_ref(const struct object_reference* ref);

extern std::string get_register_ref_name(const struct object_reference* ref);
extern std::string get_stack_ref_name(const struct object_reference* ref);
extern std::string get_global_ref_name(const struct object_reference* ref);
extern std::string get_heap_ref_name(const struct object_reference* ref);

extern bool known_global_sym(const struct object_reference* ref, address_t* sym_addr, size_t* sym_sz);
extern bool known_stack_sym(const struct object_reference* ref, address_t* sym_addr, size_t* sym_sz);
extern bool known_heap_block(const struct object_reference* ref);
extern bool global_text_ref(const struct object_reference* ref);

extern address_t get_var_addr_by_name(const char*, bool);

extern void print_func_locals (void);
extern void print_type_layout (char*);
extern void search_types_by_size(size_t, size_t);
extern bool display_object_stats(void);

extern void print_build_ids(void);

extern bool get_vtable_from_exp(const char*, std::list<struct object_range*>&, char*, size_t, size_t*);

extern bool user_request_break(void);

extern bool g_debug_core;

extern unsigned int g_ptr_bit;

extern struct ca_debug_context g_debug_context;

#define MAX_NUM_OPTIONS 32
extern int ca_parse_options(char* arg, char** out);

extern void calc_heap_usage(char* expr);

extern void init_progress_bar(unsigned long total);
extern void set_current_progress(unsigned long);
extern void end_progress_bar(void);

extern address_t ca_eval_address(const char*);

extern bool heap_command_impl(char* args);
extern bool ref_command_impl(char* args);
extern bool segment_command_impl(char* args);
extern bool pattern_command_impl(char* args);

#endif // X_DEP_H_
