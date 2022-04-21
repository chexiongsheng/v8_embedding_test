#define PESAPI_ADPT_C

#include <pesapi.h>

EXTERN_C_START

typedef pesapi_value (*pesapi_create_nullType)(pesapi_env env);
static pesapi_create_nullType pesapi_create_null_ptr;
pesapi_value pesapi_create_null (pesapi_env env) {
    return pesapi_create_null_ptr(env);
}

typedef pesapi_value (*pesapi_create_undefinedType)(pesapi_env env);
static pesapi_create_undefinedType pesapi_create_undefined_ptr;
pesapi_value pesapi_create_undefined (pesapi_env env) {
    return pesapi_create_undefined_ptr(env);
}

typedef pesapi_value (*pesapi_create_booleanType)(pesapi_env env, bool value);
static pesapi_create_booleanType pesapi_create_boolean_ptr;
pesapi_value pesapi_create_boolean (pesapi_env env, bool value) {
    return pesapi_create_boolean_ptr(env, value);
}

typedef pesapi_value (*pesapi_create_int32Type)(pesapi_env env, int32_t value);
static pesapi_create_int32Type pesapi_create_int32_ptr;
pesapi_value pesapi_create_int32 (pesapi_env env, int32_t value) {
    return pesapi_create_int32_ptr(env, value);
}

typedef pesapi_value (*pesapi_create_uint32Type)(pesapi_env env, uint32_t value);
static pesapi_create_uint32Type pesapi_create_uint32_ptr;
pesapi_value pesapi_create_uint32 (pesapi_env env, uint32_t value) {
    return pesapi_create_uint32_ptr(env, value);
}

typedef pesapi_value (*pesapi_create_int64Type)(pesapi_env env, int64_t value);
static pesapi_create_int64Type pesapi_create_int64_ptr;
pesapi_value pesapi_create_int64 (pesapi_env env, int64_t value) {
    return pesapi_create_int64_ptr(env, value);
}

typedef pesapi_value (*pesapi_create_uint64Type)(pesapi_env env, uint64_t value);
static pesapi_create_uint64Type pesapi_create_uint64_ptr;
pesapi_value pesapi_create_uint64 (pesapi_env env, uint64_t value) {
    return pesapi_create_uint64_ptr(env, value);
}

typedef pesapi_value (*pesapi_create_doubleType)(pesapi_env env, double value);
static pesapi_create_doubleType pesapi_create_double_ptr;
pesapi_value pesapi_create_double (pesapi_env env, double value) {
    return pesapi_create_double_ptr(env, value);
}

typedef pesapi_value (*pesapi_create_string_utf8Type)(pesapi_env env, const char* str, size_t length);
static pesapi_create_string_utf8Type pesapi_create_string_utf8_ptr;
pesapi_value pesapi_create_string_utf8 (pesapi_env env, const char* str, size_t length) {
    return pesapi_create_string_utf8_ptr(env, str, length);
}

typedef bool (*pesapi_get_value_boolType)(pesapi_env env, pesapi_value value);
static pesapi_get_value_boolType pesapi_get_value_bool_ptr;
bool pesapi_get_value_bool (pesapi_env env, pesapi_value value) {
    return pesapi_get_value_bool_ptr(env, value);
}

typedef int32_t (*pesapi_get_value_int32Type)(pesapi_env env, pesapi_value value);
static pesapi_get_value_int32Type pesapi_get_value_int32_ptr;
int32_t pesapi_get_value_int32 (pesapi_env env, pesapi_value value) {
    return pesapi_get_value_int32_ptr(env, value);
}

typedef uint32_t (*pesapi_get_value_uint32Type)(pesapi_env env, pesapi_value value);
static pesapi_get_value_uint32Type pesapi_get_value_uint32_ptr;
uint32_t pesapi_get_value_uint32 (pesapi_env env, pesapi_value value) {
    return pesapi_get_value_uint32_ptr(env, value);
}

typedef int64_t (*pesapi_get_value_int64Type)(pesapi_env env, pesapi_value value);
static pesapi_get_value_int64Type pesapi_get_value_int64_ptr;
int64_t pesapi_get_value_int64 (pesapi_env env, pesapi_value value) {
    return pesapi_get_value_int64_ptr(env, value);
}

typedef uint64_t (*pesapi_get_value_uint64Type)(pesapi_env env, pesapi_value value);
static pesapi_get_value_uint64Type pesapi_get_value_uint64_ptr;
uint64_t pesapi_get_value_uint64 (pesapi_env env, pesapi_value value) {
    return pesapi_get_value_uint64_ptr(env, value);
}

typedef double (*pesapi_get_value_doubleType)(pesapi_env env, pesapi_value value);
static pesapi_get_value_doubleType pesapi_get_value_double_ptr;
double pesapi_get_value_double (pesapi_env env, pesapi_value value) {
    return pesapi_get_value_double_ptr(env, value);
}

typedef bool (*pesapi_is_nullType)(pesapi_env env, pesapi_value value);
static pesapi_is_nullType pesapi_is_null_ptr;
bool pesapi_is_null (pesapi_env env, pesapi_value value) {
    return pesapi_is_null_ptr(env, value);
}

typedef bool (*pesapi_is_undefinedType)(pesapi_env env, pesapi_value value);
static pesapi_is_undefinedType pesapi_is_undefined_ptr;
bool pesapi_is_undefined (pesapi_env env, pesapi_value value) {
    return pesapi_is_undefined_ptr(env, value);
}

typedef bool (*pesapi_is_booleanType)(pesapi_env env, pesapi_value value);
static pesapi_is_booleanType pesapi_is_boolean_ptr;
bool pesapi_is_boolean (pesapi_env env, pesapi_value value) {
    return pesapi_is_boolean_ptr(env, value);
}

typedef bool (*pesapi_is_int32Type)(pesapi_env env, pesapi_value value);
static pesapi_is_int32Type pesapi_is_int32_ptr;
bool pesapi_is_int32 (pesapi_env env, pesapi_value value) {
    return pesapi_is_int32_ptr(env, value);
}

typedef bool (*pesapi_is_uint32Type)(pesapi_env env, pesapi_value value);
static pesapi_is_uint32Type pesapi_is_uint32_ptr;
bool pesapi_is_uint32 (pesapi_env env, pesapi_value value) {
    return pesapi_is_uint32_ptr(env, value);
}

typedef bool (*pesapi_is_int64Type)(pesapi_env env, pesapi_value value);
static pesapi_is_int64Type pesapi_is_int64_ptr;
bool pesapi_is_int64 (pesapi_env env, pesapi_value value) {
    return pesapi_is_int64_ptr(env, value);
}

typedef bool (*pesapi_is_uint64Type)(pesapi_env env, pesapi_value value);
static pesapi_is_uint64Type pesapi_is_uint64_ptr;
bool pesapi_is_uint64 (pesapi_env env, pesapi_value value) {
    return pesapi_is_uint64_ptr(env, value);
}

typedef bool (*pesapi_is_doubleType)(pesapi_env env, pesapi_value value);
static pesapi_is_doubleType pesapi_is_double_ptr;
bool pesapi_is_double (pesapi_env env, pesapi_value value) {
    return pesapi_is_double_ptr(env, value);
}

typedef bool (*pesapi_is_stringType)(pesapi_env env, pesapi_value value);
static pesapi_is_stringType pesapi_is_string_ptr;
bool pesapi_is_string (pesapi_env env, pesapi_value value) {
    return pesapi_is_string_ptr(env, value);
}

typedef bool (*pesapi_is_objectType)(pesapi_env env, pesapi_value value);
static pesapi_is_objectType pesapi_is_object_ptr;
bool pesapi_is_object (pesapi_env env, pesapi_value value) {
    return pesapi_is_object_ptr(env, value);
}

typedef bool (*pesapi_is_functionType)(pesapi_env env, pesapi_value value);
static pesapi_is_functionType pesapi_is_function_ptr;
bool pesapi_is_function (pesapi_env env, pesapi_value value) {
    return pesapi_is_function_ptr(env, value);
}

typedef pesapi_value (*pesapi_create_native_objectType)(pesapi_env env, const void* class_id, void* object_ptr, bool copy);
static pesapi_create_native_objectType pesapi_create_native_object_ptr;
pesapi_value pesapi_create_native_object (pesapi_env env, const void* class_id, void* object_ptr, bool copy) {
    return pesapi_create_native_object_ptr(env, class_id, object_ptr, copy);
}

typedef void* (*pesapi_get_native_object_ptrType)(pesapi_env env, pesapi_value value);
static pesapi_get_native_object_ptrType pesapi_get_native_object_ptr_ptr;
void* pesapi_get_native_object_ptr (pesapi_env env, pesapi_value value) {
    return pesapi_get_native_object_ptr_ptr(env, value);
}

typedef bool (*pesapi_is_native_objectType)(pesapi_env env, const void* class_id, pesapi_value value);
static pesapi_is_native_objectType pesapi_is_native_object_ptr;
bool pesapi_is_native_object (pesapi_env env, const void* class_id, pesapi_value value) {
    return pesapi_is_native_object_ptr(env, class_id, value);
}

typedef pesapi_value (*pesapi_create_refType)(pesapi_env env, pesapi_value value);
static pesapi_create_refType pesapi_create_ref_ptr;
pesapi_value pesapi_create_ref (pesapi_env env, pesapi_value value) {
    return pesapi_create_ref_ptr(env, value);
}

typedef pesapi_value (*pesapi_get_value_refType)(pesapi_env env, pesapi_value value);
static pesapi_get_value_refType pesapi_get_value_ref_ptr;
pesapi_value pesapi_get_value_ref (pesapi_env env, pesapi_value value) {
    return pesapi_get_value_ref_ptr(env, value);
}

typedef void (*pesapi_update_value_refType)(pesapi_env env, pesapi_value ref, pesapi_value value);
static pesapi_update_value_refType pesapi_update_value_ref_ptr;
void pesapi_update_value_ref (pesapi_env env, pesapi_value ref, pesapi_value value) {
    pesapi_update_value_ref_ptr(env, ref, value);
}

typedef bool (*pesapi_is_refType)(pesapi_env env, pesapi_value value);
static pesapi_is_refType pesapi_is_ref_ptr;
bool pesapi_is_ref (pesapi_env env, pesapi_value value) {
    return pesapi_is_ref_ptr(env, value);
}

typedef int (*pesapi_get_args_lenType)(pesapi_callback_info info);
static pesapi_get_args_lenType pesapi_get_args_len_ptr;
int pesapi_get_args_len (pesapi_callback_info info) {
    return pesapi_get_args_len_ptr(info);
}

typedef pesapi_value (*pesapi_get_argType)(pesapi_callback_info info, int index);
static pesapi_get_argType pesapi_get_arg_ptr;
pesapi_value pesapi_get_arg (pesapi_callback_info info, int index) {
    return pesapi_get_arg_ptr(info, index);
}

typedef pesapi_env (*pesapi_get_envType)(pesapi_callback_info info);
static pesapi_get_envType pesapi_get_env_ptr;
pesapi_env pesapi_get_env (pesapi_callback_info info) {
    return pesapi_get_env_ptr(info);
}

typedef pesapi_value (*pesapi_get_thisType)(pesapi_callback_info info);
static pesapi_get_thisType pesapi_get_this_ptr;
pesapi_value pesapi_get_this (pesapi_callback_info info) {
    return pesapi_get_this_ptr(info);
}

typedef pesapi_value (*pesapi_get_holderType)(pesapi_callback_info info);
static pesapi_get_holderType pesapi_get_holder_ptr;
pesapi_value pesapi_get_holder (pesapi_callback_info info) {
    return pesapi_get_holder_ptr(info);
}

typedef void (*pesapi_add_returnType)(pesapi_callback_info info, pesapi_value value);
static pesapi_add_returnType pesapi_add_return_ptr;
void pesapi_add_return (pesapi_callback_info info, pesapi_value value) {
    pesapi_add_return_ptr(info, value);
}

typedef void (*pesapi_throw_by_stringType)(pesapi_callback_info pinfo, const char* msg);
static pesapi_throw_by_stringType pesapi_throw_by_string_ptr;
void pesapi_throw_by_string (pesapi_callback_info pinfo, const char* msg) {
    pesapi_throw_by_string_ptr(pinfo, msg);
}

typedef pesapi_env_holder (*pesapi_hold_envType)(pesapi_env env);
static pesapi_hold_envType pesapi_hold_env_ptr;
pesapi_env_holder pesapi_hold_env (pesapi_env env) {
    return pesapi_hold_env_ptr(env);
}

typedef pesapi_env (*pesapi_get_env_from_holderType)(pesapi_env_holder env_holder);
static pesapi_get_env_from_holderType pesapi_get_env_from_holder_ptr;
pesapi_env pesapi_get_env_from_holder (pesapi_env_holder env_holder) {
    return pesapi_get_env_from_holder_ptr(env_holder);
}

typedef pesapi_env_holder (*pesapi_duplicate_env_holderType)(pesapi_env_holder env_holder);
static pesapi_duplicate_env_holderType pesapi_duplicate_env_holder_ptr;
pesapi_env_holder pesapi_duplicate_env_holder (pesapi_env_holder env_holder) {
    return pesapi_duplicate_env_holder_ptr(env_holder);
}

typedef void (*pesapi_release_env_holderType)(pesapi_env_holder env_holder);
static pesapi_release_env_holderType pesapi_release_env_holder_ptr;
void pesapi_release_env_holder (pesapi_env_holder env_holder) {
    pesapi_release_env_holder_ptr(env_holder);
}

typedef pesapi_scope (*pesapi_open_scopeType)(pesapi_env env);
static pesapi_open_scopeType pesapi_open_scope_ptr;
pesapi_scope pesapi_open_scope (pesapi_env env) {
    return pesapi_open_scope_ptr(env);
}

typedef bool (*pesapi_has_caughtType)(pesapi_scope scope);
static pesapi_has_caughtType pesapi_has_caught_ptr;
bool pesapi_has_caught (pesapi_scope scope) {
    return pesapi_has_caught_ptr(scope);
}

typedef void (*pesapi_close_scopeType)(pesapi_scope scope);
static pesapi_close_scopeType pesapi_close_scope_ptr;
void pesapi_close_scope (pesapi_scope scope) {
    pesapi_close_scope_ptr(scope);
}

typedef pesapi_value_holder (*pesapi_hold_valueType)(pesapi_env env, pesapi_value value);
static pesapi_hold_valueType pesapi_hold_value_ptr;
pesapi_value_holder pesapi_hold_value (pesapi_env env, pesapi_value value) {
    return pesapi_hold_value_ptr(env, value);
}

typedef pesapi_value_holder (*pesapi_duplicate_value_holderType)(pesapi_value_holder value_holder);
static pesapi_duplicate_value_holderType pesapi_duplicate_value_holder_ptr;
pesapi_value_holder pesapi_duplicate_value_holder (pesapi_value_holder value_holder) {
    return pesapi_duplicate_value_holder_ptr(value_holder);
}

typedef void (*pesapi_release_value_holderType)(pesapi_value_holder value_holder);
static pesapi_release_value_holderType pesapi_release_value_holder_ptr;
void pesapi_release_value_holder (pesapi_value_holder value_holder) {
    pesapi_release_value_holder_ptr(value_holder);
}

typedef pesapi_value (*pesapi_get_value_from_holderType)(pesapi_env env, pesapi_value_holder value_holder);
static pesapi_get_value_from_holderType pesapi_get_value_from_holder_ptr;
pesapi_value pesapi_get_value_from_holder (pesapi_env env, pesapi_value_holder value_holder) {
    return pesapi_get_value_from_holder_ptr(env, value_holder);
}

typedef pesapi_value (*pesapi_get_propertyType)(pesapi_env env, pesapi_value object, const char* key);
static pesapi_get_propertyType pesapi_get_property_ptr;
pesapi_value pesapi_get_property (pesapi_env env, pesapi_value object, const char* key) {
    return pesapi_get_property_ptr(env, object, key);
}

typedef void (*pesapi_set_propertyType)(pesapi_env env, pesapi_value object, const char* key, pesapi_value value);
static pesapi_set_propertyType pesapi_set_property_ptr;
void pesapi_set_property (pesapi_env env, pesapi_value object, const char* key, pesapi_value value) {
    pesapi_set_property_ptr(env, object, key, value);
}

typedef pesapi_value (*pesapi_call_functionType)(pesapi_env env, pesapi_value func, pesapi_value this_object, int argc, const pesapi_value argv[]);
static pesapi_call_functionType pesapi_call_function_ptr;
pesapi_value pesapi_call_function (pesapi_env env, pesapi_value func, pesapi_value this_object, int argc, const pesapi_value argv[]) {
    return pesapi_call_function_ptr(env, func, this_object, argc, argv);
}

typedef void (*pesapi_define_classType)(const void* type_id, const void* super_type_id, const char* type_name,pesapi_constructor constructor, pesapi_finalize finalize, size_t property_count, const pesapi_property_descriptor* properties);
static pesapi_define_classType pesapi_define_class_ptr;
void pesapi_define_class (const void* type_id, const void* super_type_id, const char* type_name,pesapi_constructor constructor, pesapi_finalize finalize, size_t property_count, const pesapi_property_descriptor* properties) {
    pesapi_define_class_ptr(type_id, super_type_id, type_name, constructor, finalize, property_count, properties);
}


void pesapi_init(pesapi_func_ptr* func_array){    pesapi_create_null_ptr = (pesapi_create_nullType)func_array[0];
    pesapi_create_undefined_ptr = (pesapi_create_undefinedType)func_array[1];
    pesapi_create_boolean_ptr = (pesapi_create_booleanType)func_array[2];
    pesapi_create_int32_ptr = (pesapi_create_int32Type)func_array[3];
    pesapi_create_uint32_ptr = (pesapi_create_uint32Type)func_array[4];
    pesapi_create_int64_ptr = (pesapi_create_int64Type)func_array[5];
    pesapi_create_uint64_ptr = (pesapi_create_uint64Type)func_array[6];
    pesapi_create_double_ptr = (pesapi_create_doubleType)func_array[7];
    pesapi_create_string_utf8_ptr = (pesapi_create_string_utf8Type)func_array[8];
    pesapi_get_value_bool_ptr = (pesapi_get_value_boolType)func_array[9];
    pesapi_get_value_int32_ptr = (pesapi_get_value_int32Type)func_array[10];
    pesapi_get_value_uint32_ptr = (pesapi_get_value_uint32Type)func_array[11];
    pesapi_get_value_int64_ptr = (pesapi_get_value_int64Type)func_array[12];
    pesapi_get_value_uint64_ptr = (pesapi_get_value_uint64Type)func_array[13];
    pesapi_get_value_double_ptr = (pesapi_get_value_doubleType)func_array[14];
    pesapi_is_null_ptr = (pesapi_is_nullType)func_array[15];
    pesapi_is_undefined_ptr = (pesapi_is_undefinedType)func_array[16];
    pesapi_is_boolean_ptr = (pesapi_is_booleanType)func_array[17];
    pesapi_is_int32_ptr = (pesapi_is_int32Type)func_array[18];
    pesapi_is_uint32_ptr = (pesapi_is_uint32Type)func_array[19];
    pesapi_is_int64_ptr = (pesapi_is_int64Type)func_array[20];
    pesapi_is_uint64_ptr = (pesapi_is_uint64Type)func_array[21];
    pesapi_is_double_ptr = (pesapi_is_doubleType)func_array[22];
    pesapi_is_string_ptr = (pesapi_is_stringType)func_array[23];
    pesapi_is_object_ptr = (pesapi_is_objectType)func_array[24];
    pesapi_is_function_ptr = (pesapi_is_functionType)func_array[25];
    pesapi_create_native_object_ptr = (pesapi_create_native_objectType)func_array[26];
    pesapi_get_native_object_ptr_ptr = (pesapi_get_native_object_ptrType)func_array[27];
    pesapi_is_native_object_ptr = (pesapi_is_native_objectType)func_array[28];
    pesapi_create_ref_ptr = (pesapi_create_refType)func_array[29];
    pesapi_get_value_ref_ptr = (pesapi_get_value_refType)func_array[30];
    pesapi_update_value_ref_ptr = (pesapi_update_value_refType)func_array[31];
    pesapi_is_ref_ptr = (pesapi_is_refType)func_array[32];
    pesapi_get_args_len_ptr = (pesapi_get_args_lenType)func_array[33];
    pesapi_get_arg_ptr = (pesapi_get_argType)func_array[34];
    pesapi_get_env_ptr = (pesapi_get_envType)func_array[35];
    pesapi_get_this_ptr = (pesapi_get_thisType)func_array[36];
    pesapi_get_holder_ptr = (pesapi_get_holderType)func_array[37];
    pesapi_add_return_ptr = (pesapi_add_returnType)func_array[38];
    pesapi_throw_by_string_ptr = (pesapi_throw_by_stringType)func_array[39];
    pesapi_hold_env_ptr = (pesapi_hold_envType)func_array[40];
    pesapi_get_env_from_holder_ptr = (pesapi_get_env_from_holderType)func_array[41];
    pesapi_duplicate_env_holder_ptr = (pesapi_duplicate_env_holderType)func_array[42];
    pesapi_release_env_holder_ptr = (pesapi_release_env_holderType)func_array[43];
    pesapi_open_scope_ptr = (pesapi_open_scopeType)func_array[44];
    pesapi_has_caught_ptr = (pesapi_has_caughtType)func_array[45];
    pesapi_close_scope_ptr = (pesapi_close_scopeType)func_array[46];
    pesapi_hold_value_ptr = (pesapi_hold_valueType)func_array[47];
    pesapi_duplicate_value_holder_ptr = (pesapi_duplicate_value_holderType)func_array[48];
    pesapi_release_value_holder_ptr = (pesapi_release_value_holderType)func_array[49];
    pesapi_get_value_from_holder_ptr = (pesapi_get_value_from_holderType)func_array[50];
    pesapi_get_property_ptr = (pesapi_get_propertyType)func_array[51];
    pesapi_set_property_ptr = (pesapi_set_propertyType)func_array[52];
    pesapi_call_function_ptr = (pesapi_call_functionType)func_array[53];
    pesapi_define_class_ptr = (pesapi_define_classType)func_array[54];
}

EXTERN_C_END
