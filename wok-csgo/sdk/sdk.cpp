#include "../globals.h"

c_key_values::~c_key_values() { interfaces::m_mem_alloc->free(this); }

i_handle_entity* c_base_handle::get() const { return is_valid() ? interfaces::m_entity_list->get_client_entity_from_handle(*this) : nullptr; }