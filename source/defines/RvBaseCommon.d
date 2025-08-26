#ifndef RV_BASE_COMMON_D
#define RV_BASE_COMMON_D

#define TEMPLATE_t template <typename T> 
#define SHARED_OBJECT_t shared_ptr<RvBaseObject>
#define SHARED_CONST_OBJ_t shared_ptr<const RvBaseObject>
#define SHARED_VARIANT_t variant<shared_ptr<RvBaseProperty<bool> >, shared_ptr<RvBaseProperty<string> >, shared_ptr<RvBaseProperty<uint64_t> > >
#define VARIANT_t variant<bool, string, uint64_t>

#define CHECK_VALUE( __TYPE__, __NAME__ ) holds_alternative<__TYPE__>(__NAME__)
#define   GET_VALUE( __TYPE__, __NAME__ ) get<__TYPE__>(Property(__NAME__).value())
#define   HAS_VALUE( __NAME__           ) Property(__NAME__).has_value()
#define  GET_SHARED( __TYPE__, __NAME__ ) get<shared_ptr<RvBaseProperty<__TYPE__> > >(__NAME__)
#define MAKE_SHARED( __TYPE__, __NAME__, __VALUE__ ) make_shared<RvBaseProperty<__TYPE__> >(__NAME__, get<__TYPE__>(__VALUE__))

#endif