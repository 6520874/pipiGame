#include "jsb_cocos2dx_gui_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "CocosGUI.h"

template<class T>
static JSBool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::RootedValue initializing(cx);
    JSBool isNewValid = JS_TRUE;
    JSObject* global = ScriptingCore::getInstance()->getGlobalObject();
	isNewValid = JS_GetProperty(cx, global, "initializing", &initializing) && JSVAL_TO_BOOLEAN(initializing);
	if (isNewValid)
	{
		TypeTest<T> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");

		JSObject *_tmp = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));
		return JS_TRUE;
	}

    JS_ReportError(cx, "Don't use `new cc.XXX`, please use `cc.XXX.create` instead! ");
    return JS_FALSE;
}

static JSBool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	return JS_FALSE;
}

JSClass  *jsb_cocos2d_gui_LayoutParameter_class;
JSObject *jsb_cocos2d_gui_LayoutParameter_prototype;

JSBool js_cocos2dx_gui_LayoutParameter_getLayoutType(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::LayoutParameter* cobj = (cocos2d::gui::LayoutParameter *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_LayoutParameter_getLayoutType : Invalid Native Object");
	if (argc == 0) {
		int ret = (int)cobj->getLayoutType();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_LayoutParameter_getLayoutType : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_LayoutParameter_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::LayoutParameter* ret = cocos2d::gui::LayoutParameter::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::LayoutParameter>(cx, (cocos2d::gui::LayoutParameter*)ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "js_cocos2dx_gui_LayoutParameter_create : wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_gui_LayoutParameter_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::LayoutParameter* cobj = new cocos2d::gui::LayoutParameter();
		cocos2d::Object *_ccobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::gui::LayoutParameter> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::gui::LayoutParameter");
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_LayoutParameter_constructor : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}



void js_cocos2d_gui_LayoutParameter_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LayoutParameter)", obj);
}

void js_register_cocos2dx_gui_LayoutParameter(JSContext *cx, JSObject *global) {
	jsb_cocos2d_gui_LayoutParameter_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_gui_LayoutParameter_class->name = "LayoutParameter";
	jsb_cocos2d_gui_LayoutParameter_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_gui_LayoutParameter_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_gui_LayoutParameter_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_gui_LayoutParameter_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_gui_LayoutParameter_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_gui_LayoutParameter_class->resolve = JS_ResolveStub;
	jsb_cocos2d_gui_LayoutParameter_class->convert = JS_ConvertStub;
	jsb_cocos2d_gui_LayoutParameter_class->finalize = js_cocos2d_gui_LayoutParameter_finalize;
	jsb_cocos2d_gui_LayoutParameter_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getLayoutType", js_cocos2dx_gui_LayoutParameter_getLayoutType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_gui_LayoutParameter_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_gui_LayoutParameter_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_cocos2d_gui_LayoutParameter_class,
		js_cocos2dx_gui_LayoutParameter_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "LayoutParameter", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::gui::LayoutParameter> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_gui_LayoutParameter_class;
		p->proto = jsb_cocos2d_gui_LayoutParameter_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_gui_LinearLayoutParameter_class;
JSObject *jsb_cocos2d_gui_LinearLayoutParameter_prototype;

JSBool js_cocos2dx_gui_LinearLayoutParameter_setGravity(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::LinearLayoutParameter* cobj = (cocos2d::gui::LinearLayoutParameter *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_LinearLayoutParameter_setGravity : Invalid Native Object");
	if (argc == 1) {
		cocos2d::gui::LinearGravity arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_LinearLayoutParameter_setGravity : Error processing arguments");
		cobj->setGravity(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_LinearLayoutParameter_setGravity : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_LinearLayoutParameter_getGravity(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::LinearLayoutParameter* cobj = (cocos2d::gui::LinearLayoutParameter *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_LinearLayoutParameter_getGravity : Invalid Native Object");
	if (argc == 0) {
		int ret = (int)cobj->getGravity();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_LinearLayoutParameter_getGravity : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_LinearLayoutParameter_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::LinearLayoutParameter* ret = cocos2d::gui::LinearLayoutParameter::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::LinearLayoutParameter>(cx, (cocos2d::gui::LinearLayoutParameter*)ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "js_cocos2dx_gui_LinearLayoutParameter_create : wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_gui_LinearLayoutParameter_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::LinearLayoutParameter* cobj = new cocos2d::gui::LinearLayoutParameter();
		cocos2d::Object *_ccobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::gui::LinearLayoutParameter> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::gui::LinearLayoutParameter");
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_LinearLayoutParameter_constructor : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}


extern JSObject *jsb_cocos2d_gui_LayoutParameter_prototype;

void js_cocos2d_gui_LinearLayoutParameter_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LinearLayoutParameter)", obj);
}

void js_register_cocos2dx_gui_LinearLayoutParameter(JSContext *cx, JSObject *global) {
	jsb_cocos2d_gui_LinearLayoutParameter_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_gui_LinearLayoutParameter_class->name = "LinearLayoutParameter";
	jsb_cocos2d_gui_LinearLayoutParameter_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_gui_LinearLayoutParameter_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_gui_LinearLayoutParameter_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_gui_LinearLayoutParameter_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_gui_LinearLayoutParameter_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_gui_LinearLayoutParameter_class->resolve = JS_ResolveStub;
	jsb_cocos2d_gui_LinearLayoutParameter_class->convert = JS_ConvertStub;
	jsb_cocos2d_gui_LinearLayoutParameter_class->finalize = js_cocos2d_gui_LinearLayoutParameter_finalize;
	jsb_cocos2d_gui_LinearLayoutParameter_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("setGravity", js_cocos2dx_gui_LinearLayoutParameter_setGravity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getGravity", js_cocos2dx_gui_LinearLayoutParameter_getGravity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_gui_LinearLayoutParameter_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_gui_LinearLayoutParameter_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_gui_LayoutParameter_prototype,
		jsb_cocos2d_gui_LinearLayoutParameter_class,
		js_cocos2dx_gui_LinearLayoutParameter_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "LinearLayoutParameter", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::gui::LinearLayoutParameter> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_gui_LinearLayoutParameter_class;
		p->proto = jsb_cocos2d_gui_LinearLayoutParameter_prototype;
		p->parentProto = jsb_cocos2d_gui_LayoutParameter_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_gui_RelativeLayoutParameter_class;
JSObject *jsb_cocos2d_gui_RelativeLayoutParameter_prototype;

JSBool js_cocos2dx_gui_RelativeLayoutParameter_setAlign(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::RelativeLayoutParameter* cobj = (cocos2d::gui::RelativeLayoutParameter *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_RelativeLayoutParameter_setAlign : Invalid Native Object");
	if (argc == 1) {
		cocos2d::gui::RelativeAlign arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_RelativeLayoutParameter_setAlign : Error processing arguments");
		cobj->setAlign(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_RelativeLayoutParameter_setAlign : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_RelativeLayoutParameter_setRelativeToWidgetName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::RelativeLayoutParameter* cobj = (cocos2d::gui::RelativeLayoutParameter *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_RelativeLayoutParameter_setRelativeToWidgetName : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_RelativeLayoutParameter_setRelativeToWidgetName : Error processing arguments");
		cobj->setRelativeToWidgetName(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_RelativeLayoutParameter_setRelativeToWidgetName : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_RelativeLayoutParameter_getRelativeName(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::RelativeLayoutParameter* cobj = (cocos2d::gui::RelativeLayoutParameter *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_RelativeLayoutParameter_getRelativeName : Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->getRelativeName();
		jsval jsret = JSVAL_NULL;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_RelativeLayoutParameter_getRelativeName : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_RelativeLayoutParameter_getRelativeToWidgetName(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::RelativeLayoutParameter* cobj = (cocos2d::gui::RelativeLayoutParameter *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_RelativeLayoutParameter_getRelativeToWidgetName : Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->getRelativeToWidgetName();
		jsval jsret = JSVAL_NULL;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_RelativeLayoutParameter_getRelativeToWidgetName : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_RelativeLayoutParameter_setRelativeName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::RelativeLayoutParameter* cobj = (cocos2d::gui::RelativeLayoutParameter *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_RelativeLayoutParameter_setRelativeName : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_RelativeLayoutParameter_setRelativeName : Error processing arguments");
		cobj->setRelativeName(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_RelativeLayoutParameter_setRelativeName : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_RelativeLayoutParameter_getAlign(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::RelativeLayoutParameter* cobj = (cocos2d::gui::RelativeLayoutParameter *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_RelativeLayoutParameter_getAlign : Invalid Native Object");
	if (argc == 0) {
		int ret = (int)cobj->getAlign();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_RelativeLayoutParameter_getAlign : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_RelativeLayoutParameter_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::RelativeLayoutParameter* ret = cocos2d::gui::RelativeLayoutParameter::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::RelativeLayoutParameter>(cx, (cocos2d::gui::RelativeLayoutParameter*)ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "js_cocos2dx_gui_RelativeLayoutParameter_create : wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_gui_RelativeLayoutParameter_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::RelativeLayoutParameter* cobj = new cocos2d::gui::RelativeLayoutParameter();
		cocos2d::Object *_ccobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::gui::RelativeLayoutParameter> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::gui::RelativeLayoutParameter");
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_RelativeLayoutParameter_constructor : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}


extern JSObject *jsb_cocos2d_gui_LayoutParameter_prototype;

void js_cocos2d_gui_RelativeLayoutParameter_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (RelativeLayoutParameter)", obj);
}

void js_register_cocos2dx_gui_RelativeLayoutParameter(JSContext *cx, JSObject *global) {
	jsb_cocos2d_gui_RelativeLayoutParameter_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_gui_RelativeLayoutParameter_class->name = "RelativeLayoutParameter";
	jsb_cocos2d_gui_RelativeLayoutParameter_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_gui_RelativeLayoutParameter_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_gui_RelativeLayoutParameter_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_gui_RelativeLayoutParameter_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_gui_RelativeLayoutParameter_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_gui_RelativeLayoutParameter_class->resolve = JS_ResolveStub;
	jsb_cocos2d_gui_RelativeLayoutParameter_class->convert = JS_ConvertStub;
	jsb_cocos2d_gui_RelativeLayoutParameter_class->finalize = js_cocos2d_gui_RelativeLayoutParameter_finalize;
	jsb_cocos2d_gui_RelativeLayoutParameter_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("setAlign", js_cocos2dx_gui_RelativeLayoutParameter_setAlign, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setRelativeToWidgetName", js_cocos2dx_gui_RelativeLayoutParameter_setRelativeToWidgetName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getRelativeName", js_cocos2dx_gui_RelativeLayoutParameter_getRelativeName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getRelativeToWidgetName", js_cocos2dx_gui_RelativeLayoutParameter_getRelativeToWidgetName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setRelativeName", js_cocos2dx_gui_RelativeLayoutParameter_setRelativeName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getAlign", js_cocos2dx_gui_RelativeLayoutParameter_getAlign, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_gui_RelativeLayoutParameter_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_gui_RelativeLayoutParameter_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_gui_LayoutParameter_prototype,
		jsb_cocos2d_gui_RelativeLayoutParameter_class,
		js_cocos2dx_gui_RelativeLayoutParameter_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "RelativeLayoutParameter", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::gui::RelativeLayoutParameter> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_gui_RelativeLayoutParameter_class;
		p->proto = jsb_cocos2d_gui_RelativeLayoutParameter_prototype;
		p->parentProto = jsb_cocos2d_gui_LayoutParameter_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_gui_Widget_class;
JSObject *jsb_cocos2d_gui_Widget_prototype;

JSBool js_cocos2dx_gui_Widget_getVirtualRenderer(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getVirtualRenderer : Invalid Native Object");
	if (argc == 0) {
		cocos2d::Node* ret = cobj->getVirtualRenderer();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::Node>(cx, (cocos2d::Node*)ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getVirtualRenderer : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_setSizePercent(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setSizePercent : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setSizePercent : Error processing arguments");
		cobj->setSizePercent(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_setSizePercent : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_setActionTag(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setActionTag : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setActionTag : Error processing arguments");
		cobj->setActionTag(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_setActionTag : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_getNodeByTag(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getNodeByTag : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getNodeByTag : Error processing arguments");
		cocos2d::Node* ret = cobj->getNodeByTag(arg0);
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::Node>(cx, (cocos2d::Node*)ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getNodeByTag : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_isFlipY(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_isFlipY : Invalid Native Object");
	if (argc == 0) {
		JSBool ret = cobj->isFlipY();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_isFlipY : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_getTouchEndPos(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getTouchEndPos : Invalid Native Object");
	if (argc == 0) {
		const cocos2d::Point& ret = cobj->getTouchEndPos();
		jsval jsret = JSVAL_NULL;
		jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getTouchEndPos : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_setPositionPercent(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setPositionPercent : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setPositionPercent : Error processing arguments");
		cobj->setPositionPercent(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_setPositionPercent : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_getNodes(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getNodes : Invalid Native Object");
	if (argc == 0) {
		cocos2d::Vector<cocos2d::Node *>& ret = cobj->getNodes();
		jsval jsret = JSVAL_NULL;
		jsret = ccvector_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getNodes : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_setPositionType(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setPositionType : Invalid Native Object");
	if (argc == 1) {
		cocos2d::gui::PositionType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setPositionType : Error processing arguments");
		cobj->setPositionType(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_setPositionType : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_getName(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getName : Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->getName();
		jsval jsret = JSVAL_NULL;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getName : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_isIgnoreContentAdaptWithSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_isIgnoreContentAdaptWithSize : Invalid Native Object");
	if (argc == 0) {
		JSBool ret = cobj->isIgnoreContentAdaptWithSize();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_isIgnoreContentAdaptWithSize : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_updateSizeAndPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_updateSizeAndPosition : Invalid Native Object");
	if (argc == 0) {
		cobj->updateSizeAndPosition();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_updateSizeAndPosition : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_getBottomInParent(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getBottomInParent : Invalid Native Object");
	if (argc == 0) {
		double ret = cobj->getBottomInParent();
		jsval jsret = JSVAL_NULL;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getBottomInParent : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_getActionTag(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getActionTag : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getActionTag();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getActionTag : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_getLayoutParameter(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getLayoutParameter : Invalid Native Object");
	if (argc == 1) {
		cocos2d::gui::LayoutParameterType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getLayoutParameter : Error processing arguments");
		cocos2d::gui::LayoutParameter* ret = cobj->getLayoutParameter(arg0);
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::LayoutParameter>(cx, (cocos2d::gui::LayoutParameter*)ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getLayoutParameter : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_getPositionType(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getPositionType : Invalid Native Object");
	if (argc == 0) {
		int ret = (int)cobj->getPositionType();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getPositionType : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_setName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setName : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setName : Error processing arguments");
		cobj->setName(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_setName : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_getChildByName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getChildByName : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getChildByName : Error processing arguments");
		cocos2d::gui::Widget* ret = cobj->getChildByName(arg0);
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::Widget>(cx, (cocos2d::gui::Widget*)ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getChildByName : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_isEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_isEnabled : Invalid Native Object");
	if (argc == 0) {
		JSBool ret = cobj->isEnabled();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_isEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_isFlipX(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_isFlipX : Invalid Native Object");
	if (argc == 0) {
		JSBool ret = cobj->isFlipX();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_isFlipX : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_removeNodeByTag(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_removeNodeByTag : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_removeNodeByTag : Error processing arguments");
		cobj->removeNodeByTag(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_removeNodeByTag : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_isTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_isTouchEnabled : Invalid Native Object");
	if (argc == 0) {
		JSBool ret = cobj->isTouchEnabled();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_isTouchEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_getContentSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getContentSize : Invalid Native Object");
	if (argc == 0) {
		const cocos2d::Size& ret = cobj->getContentSize();
		jsval jsret = JSVAL_NULL;
		jsret = ccsize_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getContentSize : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_getTouchStartPos(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getTouchStartPos : Invalid Native Object");
	if (argc == 0) {
		const cocos2d::Point& ret = cobj->getTouchStartPos();
		jsval jsret = JSVAL_NULL;
		jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getTouchStartPos : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_didNotSelectSelf(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_didNotSelectSelf : Invalid Native Object");
	if (argc == 0) {
		cobj->didNotSelectSelf();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_didNotSelectSelf : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_setFocused(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setFocused : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setFocused : Error processing arguments");
		cobj->setFocused(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_setFocused : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_setTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setTouchEnabled : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setTouchEnabled : Error processing arguments");
		cobj->setTouchEnabled(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_setTouchEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_clone(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_clone : Invalid Native Object");
	if (argc == 0) {
		cocos2d::gui::Widget* ret = cobj->clone();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::Widget>(cx, (cocos2d::gui::Widget*)ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_clone : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_getTouchMovePos(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getTouchMovePos : Invalid Native Object");
	if (argc == 0) {
		const cocos2d::Point& ret = cobj->getTouchMovePos();
		jsval jsret = JSVAL_NULL;
		jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getTouchMovePos : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_setEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setEnabled : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setEnabled : Error processing arguments");
		cobj->setEnabled(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_setEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_setBrightStyle(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setBrightStyle : Invalid Native Object");
	if (argc == 1) {
		cocos2d::gui::BrightStyle arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setBrightStyle : Error processing arguments");
		cobj->setBrightStyle(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_setBrightStyle : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_addNode(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	cocos2d::gui::Widget* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_addNode : Invalid Native Object");
	do {
		if (argc == 2) {
			cocos2d::Node* arg0;
			do {
				if (!argv[0].isObject()) { ok = JS_FALSE; break; }
				js_proxy_t *proxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
				proxy = jsb_get_js_proxy(tmpObj);
				arg0 = (cocos2d::Node*)(proxy ? proxy->ptr : NULL);
				JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = JS_TRUE; break; }
			int arg1;
			ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
			if (!ok) { ok = JS_TRUE; break; }
			cobj->addNode(arg0, arg1);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			cocos2d::Node* arg0;
			do {
				if (!argv[0].isObject()) { ok = JS_FALSE; break; }
				js_proxy_t *proxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
				proxy = jsb_get_js_proxy(tmpObj);
				arg0 = (cocos2d::Node*)(proxy ? proxy->ptr : NULL);
				JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = JS_TRUE; break; }
			cobj->addNode(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 3) {
			cocos2d::Node* arg0;
			do {
				if (!argv[0].isObject()) { ok = JS_FALSE; break; }
				js_proxy_t *proxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
				proxy = jsb_get_js_proxy(tmpObj);
				arg0 = (cocos2d::Node*)(proxy ? proxy->ptr : NULL);
				JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = JS_TRUE; break; }
			int arg1;
			ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
			if (!ok) { ok = JS_TRUE; break; }
			int arg2;
			ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
			if (!ok) { ok = JS_TRUE; break; }
			cobj->addNode(arg0, arg1, arg2);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_addNode : wrong number of arguments");
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_setLayoutParameter(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setLayoutParameter : Invalid Native Object");
	if (argc == 1) {
		cocos2d::gui::LayoutParameter* arg0;
		do {
			if (!argv[0].isObject()) { ok = JS_FALSE; break; }
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::gui::LayoutParameter*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setLayoutParameter : Error processing arguments");
		cobj->setLayoutParameter(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_setLayoutParameter : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_setFlipY(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setFlipY : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setFlipY : Error processing arguments");
		cobj->setFlipY(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_setFlipY : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_setFlipX(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setFlipX : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setFlipX : Error processing arguments");
		cobj->setFlipX(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_setFlipX : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_getLeftInParent(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getLeftInParent : Invalid Native Object");
	if (argc == 0) {
		double ret = cobj->getLeftInParent();
		jsval jsret = JSVAL_NULL;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getLeftInParent : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_ignoreContentAdaptWithSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_ignoreContentAdaptWithSize : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_ignoreContentAdaptWithSize : Error processing arguments");
		cobj->ignoreContentAdaptWithSize(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_ignoreContentAdaptWithSize : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_isBright(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_isBright : Invalid Native Object");
	if (argc == 0) {
		JSBool ret = cobj->isBright();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_isBright : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_clippingParentAreaContainPoint(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_clippingParentAreaContainPoint : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_clippingParentAreaContainPoint : Error processing arguments");
		JSBool ret = cobj->clippingParentAreaContainPoint(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_clippingParentAreaContainPoint : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_getSizePercent(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getSizePercent : Invalid Native Object");
	if (argc == 0) {
		const cocos2d::Point& ret = cobj->getSizePercent();
		jsval jsret = JSVAL_NULL;
		jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getSizePercent : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_getTopInParent(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getTopInParent : Invalid Native Object");
	if (argc == 0) {
		double ret = cobj->getTopInParent();
		jsval jsret = JSVAL_NULL;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getTopInParent : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_getWidgetType(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getWidgetType : Invalid Native Object");
	if (argc == 0) {
		int ret = (int)cobj->getWidgetType();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getWidgetType : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_getSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getSize : Invalid Native Object");
	if (argc == 0) {
		const cocos2d::Size& ret = cobj->getSize();
		jsval jsret = JSVAL_NULL;
		jsret = ccsize_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getSize : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_getRightInParent(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getRightInParent : Invalid Native Object");
	if (argc == 0) {
		double ret = cobj->getRightInParent();
		jsval jsret = JSVAL_NULL;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getRightInParent : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_getSizeType(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getSizeType : Invalid Native Object");
	if (argc == 0) {
		int ret = (int)cobj->getSizeType();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getSizeType : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_removeNode(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_removeNode : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Node* arg0;
		do {
			if (!argv[0].isObject()) { ok = JS_FALSE; break; }
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::Node*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_removeNode : Error processing arguments");
		cobj->removeNode(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_removeNode : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_removeAllNodes(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_removeAllNodes : Invalid Native Object");
	if (argc == 0) {
		cobj->removeAllNodes();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_removeAllNodes : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_getWorldPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getWorldPosition : Invalid Native Object");
	if (argc == 0) {
		cocos2d::Point ret = cobj->getWorldPosition();
		jsval jsret = JSVAL_NULL;
		jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getWorldPosition : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_getPositionPercent(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_getPositionPercent : Invalid Native Object");
	if (argc == 0) {
		const cocos2d::Point& ret = cobj->getPositionPercent();
		jsval jsret = JSVAL_NULL;
		jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_getPositionPercent : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_hitTest(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_hitTest : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_hitTest : Error processing arguments");
		JSBool ret = cobj->hitTest(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_hitTest : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_isFocused(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_isFocused : Invalid Native Object");
	if (argc == 0) {
		JSBool ret = cobj->isFocused();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_isFocused : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_setSizeType(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setSizeType : Invalid Native Object");
	if (argc == 1) {
		cocos2d::gui::SizeType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setSizeType : Error processing arguments");
		cobj->setSizeType(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_setSizeType : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_checkChildInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_checkChildInfo : Invalid Native Object");
	if (argc == 3) {
		int arg0;
		cocos2d::gui::Widget* arg1;
		cocos2d::Point arg2;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		do {
			if (!argv[1].isObject()) { ok = JS_FALSE; break; }
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::gui::Widget*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		ok &= jsval_to_ccpoint(cx, argv[2], &arg2);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_checkChildInfo : Error processing arguments");
		cobj->checkChildInfo(arg0, arg1, arg2);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_checkChildInfo : wrong number of arguments: %d, was expecting %d", argc, 3);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_setSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setSize : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Size arg0;
		ok &= jsval_to_ccsize(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setSize : Error processing arguments");
		cobj->setSize(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_setSize : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_setBright(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Widget* cobj = (cocos2d::gui::Widget *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setBright : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Widget_setBright : Error processing arguments");
		cobj->setBright(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_setBright : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Widget_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::Widget* ret = cocos2d::gui::Widget::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::Widget>(cx, (cocos2d::gui::Widget*)ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "js_cocos2dx_gui_Widget_create : wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_gui_Widget_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::Widget* cobj = new cocos2d::gui::Widget();
		cocos2d::Object *_ccobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::gui::Widget> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::gui::Widget");
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Widget_constructor : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}


extern JSObject *jsb_cocos2d_Node_prototype;

void js_cocos2d_gui_Widget_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Widget)", obj);
}

void js_register_cocos2dx_gui_Widget(JSContext *cx, JSObject *global) {
	jsb_cocos2d_gui_Widget_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_gui_Widget_class->name = "Widget";
	jsb_cocos2d_gui_Widget_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_gui_Widget_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_gui_Widget_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_gui_Widget_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_gui_Widget_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_gui_Widget_class->resolve = JS_ResolveStub;
	jsb_cocos2d_gui_Widget_class->convert = JS_ConvertStub;
	jsb_cocos2d_gui_Widget_class->finalize = js_cocos2d_gui_Widget_finalize;
	jsb_cocos2d_gui_Widget_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getVirtualRenderer", js_cocos2dx_gui_Widget_getVirtualRenderer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setSizePercent", js_cocos2dx_gui_Widget_setSizePercent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setActionTag", js_cocos2dx_gui_Widget_setActionTag, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getNodeByTag", js_cocos2dx_gui_Widget_getNodeByTag, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isFlipY", js_cocos2dx_gui_Widget_isFlipY, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getTouchEndPos", js_cocos2dx_gui_Widget_getTouchEndPos, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setPositionPercent", js_cocos2dx_gui_Widget_setPositionPercent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getNodes", js_cocos2dx_gui_Widget_getNodes, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setPositionType", js_cocos2dx_gui_Widget_setPositionType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getName", js_cocos2dx_gui_Widget_getName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isIgnoreContentAdaptWithSize", js_cocos2dx_gui_Widget_isIgnoreContentAdaptWithSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("updateSizeAndPosition", js_cocos2dx_gui_Widget_updateSizeAndPosition, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getBottomInParent", js_cocos2dx_gui_Widget_getBottomInParent, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getActionTag", js_cocos2dx_gui_Widget_getActionTag, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getLayoutParameter", js_cocos2dx_gui_Widget_getLayoutParameter, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPositionType", js_cocos2dx_gui_Widget_getPositionType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setName", js_cocos2dx_gui_Widget_setName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getChildByName", js_cocos2dx_gui_Widget_getChildByName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isEnabled", js_cocos2dx_gui_Widget_isEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isFlipX", js_cocos2dx_gui_Widget_isFlipX, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("removeNodeByTag", js_cocos2dx_gui_Widget_removeNodeByTag, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isTouchEnabled", js_cocos2dx_gui_Widget_isTouchEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getContentSize", js_cocos2dx_gui_Widget_getContentSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getTouchStartPos", js_cocos2dx_gui_Widget_getTouchStartPos, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("didNotSelectSelf", js_cocos2dx_gui_Widget_didNotSelectSelf, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setFocused", js_cocos2dx_gui_Widget_setFocused, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setTouchEnabled", js_cocos2dx_gui_Widget_setTouchEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("clone", js_cocos2dx_gui_Widget_clone, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getTouchMovePos", js_cocos2dx_gui_Widget_getTouchMovePos, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setEnabled", js_cocos2dx_gui_Widget_setEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setBrightStyle", js_cocos2dx_gui_Widget_setBrightStyle, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("addNode", js_cocos2dx_gui_Widget_addNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setLayoutParameter", js_cocos2dx_gui_Widget_setLayoutParameter, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setFlipY", js_cocos2dx_gui_Widget_setFlipY, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setFlipX", js_cocos2dx_gui_Widget_setFlipX, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getLeftInParent", js_cocos2dx_gui_Widget_getLeftInParent, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("ignoreContentAdaptWithSize", js_cocos2dx_gui_Widget_ignoreContentAdaptWithSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isBright", js_cocos2dx_gui_Widget_isBright, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("clippingParentAreaContainPoint", js_cocos2dx_gui_Widget_clippingParentAreaContainPoint, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getSizePercent", js_cocos2dx_gui_Widget_getSizePercent, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getTopInParent", js_cocos2dx_gui_Widget_getTopInParent, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getWidgetType", js_cocos2dx_gui_Widget_getWidgetType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getSize", js_cocos2dx_gui_Widget_getSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getRightInParent", js_cocos2dx_gui_Widget_getRightInParent, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getSizeType", js_cocos2dx_gui_Widget_getSizeType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("removeNode", js_cocos2dx_gui_Widget_removeNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("removeAllNodes", js_cocos2dx_gui_Widget_removeAllNodes, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getWorldPosition", js_cocos2dx_gui_Widget_getWorldPosition, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPositionPercent", js_cocos2dx_gui_Widget_getPositionPercent, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("hitTest", js_cocos2dx_gui_Widget_hitTest, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isFocused", js_cocos2dx_gui_Widget_isFocused, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setSizeType", js_cocos2dx_gui_Widget_setSizeType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("checkChildInfo", js_cocos2dx_gui_Widget_checkChildInfo, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setSize", js_cocos2dx_gui_Widget_setSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setBright", js_cocos2dx_gui_Widget_setBright, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_gui_Widget_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_gui_Widget_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_Node_prototype,
		jsb_cocos2d_gui_Widget_class,
		js_cocos2dx_gui_Widget_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "Widget", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::gui::Widget> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_gui_Widget_class;
		p->proto = jsb_cocos2d_gui_Widget_prototype;
		p->parentProto = jsb_cocos2d_Node_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_gui_Layout_class;
JSObject *jsb_cocos2d_gui_Layout_prototype;

JSBool js_cocos2dx_gui_Layout_setBackGroundColorVector(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Layout* cobj = (cocos2d::gui::Layout *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Layout_setBackGroundColorVector : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Layout_setBackGroundColorVector : Error processing arguments");
		cobj->setBackGroundColorVector(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Layout_setBackGroundColorVector : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Layout_hitTest(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Layout* cobj = (cocos2d::gui::Layout *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Layout_hitTest : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Layout_hitTest : Error processing arguments");
		JSBool ret = cobj->hitTest(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Layout_hitTest : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Layout_getBackGroundImageTextureSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Layout* cobj = (cocos2d::gui::Layout *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Layout_getBackGroundImageTextureSize : Invalid Native Object");
	if (argc == 0) {
		const cocos2d::Size& ret = cobj->getBackGroundImageTextureSize();
		jsval jsret = JSVAL_NULL;
		jsret = ccsize_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Layout_getBackGroundImageTextureSize : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Layout_getLayoutType(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Layout* cobj = (cocos2d::gui::Layout *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Layout_getLayoutType : Invalid Native Object");
	if (argc == 0) {
		int ret = (int)cobj->getLayoutType();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Layout_getLayoutType : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Layout_setClippingType(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Layout* cobj = (cocos2d::gui::Layout *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Layout_setClippingType : Invalid Native Object");
	if (argc == 1) {
		cocos2d::gui::LayoutClippingType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Layout_setClippingType : Error processing arguments");
		cobj->setClippingType(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Layout_setClippingType : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Layout_setBackGroundColorType(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Layout* cobj = (cocos2d::gui::Layout *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Layout_setBackGroundColorType : Invalid Native Object");
	if (argc == 1) {
		cocos2d::gui::LayoutBackGroundColorType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Layout_setBackGroundColorType : Error processing arguments");
		cobj->setBackGroundColorType(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Layout_setBackGroundColorType : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Layout_setBackGroundImage(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Layout* cobj = (cocos2d::gui::Layout *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Layout_setBackGroundImage : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Layout_setBackGroundImage : Error processing arguments");
		cobj->setBackGroundImage(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 2) {
		const char* arg0;
		cocos2d::gui::TextureResType arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Layout_setBackGroundImage : Error processing arguments");
		cobj->setBackGroundImage(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Layout_setBackGroundImage : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Layout_setBackGroundColor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	cocos2d::gui::Layout* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (cocos2d::gui::Layout *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Layout_setBackGroundColor : Invalid Native Object");
	do {
		if (argc == 2) {
			cocos2d::Color3B arg0;
			ok &= jsval_to_cccolor3b(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			cocos2d::Color3B arg1;
			ok &= jsval_to_cccolor3b(cx, argv[1], &arg1);
			if (!ok) { ok = JS_TRUE; break; }
			cobj->setBackGroundColor(arg0, arg1);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			cocos2d::Color3B arg0;
			ok &= jsval_to_cccolor3b(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			cobj->setBackGroundColor(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "js_cocos2dx_gui_Layout_setBackGroundColor : wrong number of arguments");
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Layout_requestDoLayout(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Layout* cobj = (cocos2d::gui::Layout *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Layout_requestDoLayout : Invalid Native Object");
	if (argc == 0) {
		cobj->requestDoLayout();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Layout_requestDoLayout : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Layout_isClippingEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Layout* cobj = (cocos2d::gui::Layout *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Layout_isClippingEnabled : Invalid Native Object");
	if (argc == 0) {
		JSBool ret = cobj->isClippingEnabled();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Layout_isClippingEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Layout_setBackGroundColorOpacity(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Layout* cobj = (cocos2d::gui::Layout *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Layout_setBackGroundColorOpacity : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Layout_setBackGroundColorOpacity : Error processing arguments");
		cobj->setBackGroundColorOpacity(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Layout_setBackGroundColorOpacity : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Layout_setBackGroundImageCapInsets(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Layout* cobj = (cocos2d::gui::Layout *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Layout_setBackGroundImageCapInsets : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Rect arg0;
		ok &= jsval_to_ccrect(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Layout_setBackGroundImageCapInsets : Error processing arguments");
		cobj->setBackGroundImageCapInsets(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Layout_setBackGroundImageCapInsets : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Layout_removeBackGroundImage(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Layout* cobj = (cocos2d::gui::Layout *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Layout_removeBackGroundImage : Invalid Native Object");
	if (argc == 0) {
		cobj->removeBackGroundImage();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Layout_removeBackGroundImage : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Layout_setBackGroundImageScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Layout* cobj = (cocos2d::gui::Layout *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Layout_setBackGroundImageScale9Enabled : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Layout_setBackGroundImageScale9Enabled : Error processing arguments");
		cobj->setBackGroundImageScale9Enabled(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Layout_setBackGroundImageScale9Enabled : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Layout_setClippingEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Layout* cobj = (cocos2d::gui::Layout *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Layout_setClippingEnabled : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Layout_setClippingEnabled : Error processing arguments");
		cobj->setClippingEnabled(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Layout_setClippingEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Layout_setLayoutType(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Layout* cobj = (cocos2d::gui::Layout *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Layout_setLayoutType : Invalid Native Object");
	if (argc == 1) {
		cocos2d::gui::LayoutType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Layout_setLayoutType : Error processing arguments");
		cobj->setLayoutType(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Layout_setLayoutType : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Layout_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::Layout* ret = cocos2d::gui::Layout::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::Layout>(cx, (cocos2d::gui::Layout*)ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "js_cocos2dx_gui_Layout_create : wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_gui_Layout_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::Layout* cobj = new cocos2d::gui::Layout();
		cocos2d::Object *_ccobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::gui::Layout> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::gui::Layout");
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Layout_constructor : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}


extern JSObject *jsb_cocos2d_gui_Widget_prototype;

void js_cocos2d_gui_Layout_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Layout)", obj);
}

void js_register_cocos2dx_gui_Layout(JSContext *cx, JSObject *global) {
	jsb_cocos2d_gui_Layout_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_gui_Layout_class->name = "Layout";
	jsb_cocos2d_gui_Layout_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_gui_Layout_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_gui_Layout_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_gui_Layout_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_gui_Layout_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_gui_Layout_class->resolve = JS_ResolveStub;
	jsb_cocos2d_gui_Layout_class->convert = JS_ConvertStub;
	jsb_cocos2d_gui_Layout_class->finalize = js_cocos2d_gui_Layout_finalize;
	jsb_cocos2d_gui_Layout_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("setBackGroundColorVector", js_cocos2dx_gui_Layout_setBackGroundColorVector, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("hitTest", js_cocos2dx_gui_Layout_hitTest, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getBackGroundImageTextureSize", js_cocos2dx_gui_Layout_getBackGroundImageTextureSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getLayoutType", js_cocos2dx_gui_Layout_getLayoutType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setClippingType", js_cocos2dx_gui_Layout_setClippingType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setBackGroundColorType", js_cocos2dx_gui_Layout_setBackGroundColorType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setBackGroundImage", js_cocos2dx_gui_Layout_setBackGroundImage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setBackGroundColor", js_cocos2dx_gui_Layout_setBackGroundColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("requestDoLayout", js_cocos2dx_gui_Layout_requestDoLayout, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isClippingEnabled", js_cocos2dx_gui_Layout_isClippingEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setBackGroundColorOpacity", js_cocos2dx_gui_Layout_setBackGroundColorOpacity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setBackGroundImageCapInsets", js_cocos2dx_gui_Layout_setBackGroundImageCapInsets, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("removeBackGroundImage", js_cocos2dx_gui_Layout_removeBackGroundImage, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setBackGroundImageScale9Enabled", js_cocos2dx_gui_Layout_setBackGroundImageScale9Enabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setClippingEnabled", js_cocos2dx_gui_Layout_setClippingEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setLayoutType", js_cocos2dx_gui_Layout_setLayoutType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_gui_Layout_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_gui_Layout_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_gui_Widget_prototype,
		jsb_cocos2d_gui_Layout_class,
		js_cocos2dx_gui_Layout_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "Layout", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::gui::Layout> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_gui_Layout_class;
		p->proto = jsb_cocos2d_gui_Layout_prototype;
		p->parentProto = jsb_cocos2d_gui_Widget_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_gui_Button_class;
JSObject *jsb_cocos2d_gui_Button_prototype;

JSBool js_cocos2dx_gui_Button_getTitleText(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Button* cobj = (cocos2d::gui::Button *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Button_getTitleText : Invalid Native Object");
	if (argc == 0) {
		const std::string& ret = cobj->getTitleText();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Button_getTitleText : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Button_loadTextureNormal(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Button* cobj = (cocos2d::gui::Button *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Button_loadTextureNormal : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Button_loadTextureNormal : Error processing arguments");
		cobj->loadTextureNormal(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 2) {
		const char* arg0;
		cocos2d::gui::TextureResType arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Button_loadTextureNormal : Error processing arguments");
		cobj->loadTextureNormal(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Button_loadTextureNormal : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Button_setCapInsetsNormalRenderer(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Button* cobj = (cocos2d::gui::Button *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Button_setCapInsetsNormalRenderer : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Rect arg0;
		ok &= jsval_to_ccrect(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Button_setCapInsetsNormalRenderer : Error processing arguments");
		cobj->setCapInsetsNormalRenderer(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Button_setCapInsetsNormalRenderer : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Button_setCapInsetsPressedRenderer(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Button* cobj = (cocos2d::gui::Button *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Button_setCapInsetsPressedRenderer : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Rect arg0;
		ok &= jsval_to_ccrect(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Button_setCapInsetsPressedRenderer : Error processing arguments");
		cobj->setCapInsetsPressedRenderer(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Button_setCapInsetsPressedRenderer : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Button_loadTexturePressed(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Button* cobj = (cocos2d::gui::Button *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Button_loadTexturePressed : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Button_loadTexturePressed : Error processing arguments");
		cobj->loadTexturePressed(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 2) {
		const char* arg0;
		cocos2d::gui::TextureResType arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Button_loadTexturePressed : Error processing arguments");
		cobj->loadTexturePressed(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Button_loadTexturePressed : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Button_setTitleFontSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Button* cobj = (cocos2d::gui::Button *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Button_setTitleFontSize : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS_ValueToNumber(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Button_setTitleFontSize : Error processing arguments");
		cobj->setTitleFontSize(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Button_setTitleFontSize : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Button_setCapInsetsDisabledRenderer(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Button* cobj = (cocos2d::gui::Button *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Button_setCapInsetsDisabledRenderer : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Rect arg0;
		ok &= jsval_to_ccrect(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Button_setCapInsetsDisabledRenderer : Error processing arguments");
		cobj->setCapInsetsDisabledRenderer(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Button_setCapInsetsDisabledRenderer : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Button_setTitleFontName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Button* cobj = (cocos2d::gui::Button *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Button_setTitleFontName : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Button_setTitleFontName : Error processing arguments");
		cobj->setTitleFontName(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Button_setTitleFontName : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Button_getTitleColor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Button* cobj = (cocos2d::gui::Button *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Button_getTitleColor : Invalid Native Object");
	if (argc == 0) {
		const cocos2d::Color3B& ret = cobj->getTitleColor();
		jsval jsret = JSVAL_NULL;
		jsret = cccolor3b_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Button_getTitleColor : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Button_loadTextureDisabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Button* cobj = (cocos2d::gui::Button *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Button_loadTextureDisabled : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Button_loadTextureDisabled : Error processing arguments");
		cobj->loadTextureDisabled(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 2) {
		const char* arg0;
		cocos2d::gui::TextureResType arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Button_loadTextureDisabled : Error processing arguments");
		cobj->loadTextureDisabled(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Button_loadTextureDisabled : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Button_getTitleFontName(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Button* cobj = (cocos2d::gui::Button *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Button_getTitleFontName : Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->getTitleFontName();
		jsval jsret = JSVAL_NULL;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Button_getTitleFontName : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Button_setPressedActionEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Button* cobj = (cocos2d::gui::Button *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Button_setPressedActionEnabled : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Button_setPressedActionEnabled : Error processing arguments");
		cobj->setPressedActionEnabled(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Button_setPressedActionEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Button_setCapInsets(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Button* cobj = (cocos2d::gui::Button *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Button_setCapInsets : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Rect arg0;
		ok &= jsval_to_ccrect(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Button_setCapInsets : Error processing arguments");
		cobj->setCapInsets(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Button_setCapInsets : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Button_setScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Button* cobj = (cocos2d::gui::Button *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Button_setScale9Enabled : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Button_setScale9Enabled : Error processing arguments");
		cobj->setScale9Enabled(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Button_setScale9Enabled : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Button_loadTextures(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Button* cobj = (cocos2d::gui::Button *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Button_loadTextures : Invalid Native Object");
	if (argc == 3) {
		const char* arg0;
		const char* arg1;
		const char* arg2;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		std::string arg2_tmp; ok &= jsval_to_std_string(cx, argv[2], &arg2_tmp); arg2 = arg2_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Button_loadTextures : Error processing arguments");
		cobj->loadTextures(arg0, arg1, arg2);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 4) {
		const char* arg0;
		const char* arg1;
		const char* arg2;
		cocos2d::gui::TextureResType arg3;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		std::string arg2_tmp; ok &= jsval_to_std_string(cx, argv[2], &arg2_tmp); arg2 = arg2_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[3], (int32_t *)&arg3);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Button_loadTextures : Error processing arguments");
		cobj->loadTextures(arg0, arg1, arg2, arg3);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Button_loadTextures : wrong number of arguments: %d, was expecting %d", argc, 3);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Button_getTitleFontSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Button* cobj = (cocos2d::gui::Button *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Button_getTitleFontSize : Invalid Native Object");
	if (argc == 0) {
		double ret = cobj->getTitleFontSize();
		jsval jsret = JSVAL_NULL;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Button_getTitleFontSize : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Button_setTitleText(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Button* cobj = (cocos2d::gui::Button *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Button_setTitleText : Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Button_setTitleText : Error processing arguments");
		cobj->setTitleText(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Button_setTitleText : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Button_setTitleColor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Button* cobj = (cocos2d::gui::Button *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Button_setTitleColor : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Color3B arg0;
		ok &= jsval_to_cccolor3b(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Button_setTitleColor : Error processing arguments");
		cobj->setTitleColor(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Button_setTitleColor : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Button_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::Button* ret = cocos2d::gui::Button::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::Button>(cx, (cocos2d::gui::Button*)ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "js_cocos2dx_gui_Button_create : wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_gui_Button_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::Button* cobj = new cocos2d::gui::Button();
		cocos2d::Object *_ccobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::gui::Button> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::gui::Button");
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Button_constructor : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}


extern JSObject *jsb_cocos2d_gui_Widget_prototype;

void js_cocos2d_gui_Button_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Button)", obj);
}

void js_register_cocos2dx_gui_Button(JSContext *cx, JSObject *global) {
	jsb_cocos2d_gui_Button_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_gui_Button_class->name = "Button";
	jsb_cocos2d_gui_Button_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_gui_Button_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_gui_Button_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_gui_Button_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_gui_Button_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_gui_Button_class->resolve = JS_ResolveStub;
	jsb_cocos2d_gui_Button_class->convert = JS_ConvertStub;
	jsb_cocos2d_gui_Button_class->finalize = js_cocos2d_gui_Button_finalize;
	jsb_cocos2d_gui_Button_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getTitleText", js_cocos2dx_gui_Button_getTitleText, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadTextureNormal", js_cocos2dx_gui_Button_loadTextureNormal, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCapInsetsNormalRenderer", js_cocos2dx_gui_Button_setCapInsetsNormalRenderer, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCapInsetsPressedRenderer", js_cocos2dx_gui_Button_setCapInsetsPressedRenderer, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadTexturePressed", js_cocos2dx_gui_Button_loadTexturePressed, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setTitleFontSize", js_cocos2dx_gui_Button_setTitleFontSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCapInsetsDisabledRenderer", js_cocos2dx_gui_Button_setCapInsetsDisabledRenderer, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setTitleFontName", js_cocos2dx_gui_Button_setTitleFontName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getTitleColor", js_cocos2dx_gui_Button_getTitleColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadTextureDisabled", js_cocos2dx_gui_Button_loadTextureDisabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getTitleFontName", js_cocos2dx_gui_Button_getTitleFontName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setPressedActionEnabled", js_cocos2dx_gui_Button_setPressedActionEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCapInsets", js_cocos2dx_gui_Button_setCapInsets, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setScale9Enabled", js_cocos2dx_gui_Button_setScale9Enabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadTextures", js_cocos2dx_gui_Button_loadTextures, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getTitleFontSize", js_cocos2dx_gui_Button_getTitleFontSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setTitleText", js_cocos2dx_gui_Button_setTitleText, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setTitleColor", js_cocos2dx_gui_Button_setTitleColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_gui_Button_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_gui_Button_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_gui_Widget_prototype,
		jsb_cocos2d_gui_Button_class,
		js_cocos2dx_gui_Button_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "Button", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::gui::Button> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_gui_Button_class;
		p->proto = jsb_cocos2d_gui_Button_prototype;
		p->parentProto = jsb_cocos2d_gui_Widget_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_gui_CheckBox_class;
JSObject *jsb_cocos2d_gui_CheckBox_prototype;

JSBool js_cocos2dx_gui_CheckBox_getSelectedState(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::CheckBox* cobj = (cocos2d::gui::CheckBox *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_CheckBox_getSelectedState : Invalid Native Object");
	if (argc == 0) {
		JSBool ret = cobj->getSelectedState();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_CheckBox_getSelectedState : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_CheckBox_loadTextureBackGroundSelected(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::CheckBox* cobj = (cocos2d::gui::CheckBox *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_CheckBox_loadTextureBackGroundSelected : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_CheckBox_loadTextureBackGroundSelected : Error processing arguments");
		cobj->loadTextureBackGroundSelected(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 2) {
		const char* arg0;
		cocos2d::gui::TextureResType arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_CheckBox_loadTextureBackGroundSelected : Error processing arguments");
		cobj->loadTextureBackGroundSelected(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_CheckBox_loadTextureBackGroundSelected : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_CheckBox_loadTextureBackGroundDisabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::CheckBox* cobj = (cocos2d::gui::CheckBox *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_CheckBox_loadTextureBackGroundDisabled : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_CheckBox_loadTextureBackGroundDisabled : Error processing arguments");
		cobj->loadTextureBackGroundDisabled(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 2) {
		const char* arg0;
		cocos2d::gui::TextureResType arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_CheckBox_loadTextureBackGroundDisabled : Error processing arguments");
		cobj->loadTextureBackGroundDisabled(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_CheckBox_loadTextureBackGroundDisabled : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_CheckBox_loadTextureFrontCross(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::CheckBox* cobj = (cocos2d::gui::CheckBox *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_CheckBox_loadTextureFrontCross : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_CheckBox_loadTextureFrontCross : Error processing arguments");
		cobj->loadTextureFrontCross(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 2) {
		const char* arg0;
		cocos2d::gui::TextureResType arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_CheckBox_loadTextureFrontCross : Error processing arguments");
		cobj->loadTextureFrontCross(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_CheckBox_loadTextureFrontCross : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_CheckBox_loadTextures(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::CheckBox* cobj = (cocos2d::gui::CheckBox *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_CheckBox_loadTextures : Invalid Native Object");
	if (argc == 5) {
		const char* arg0;
		const char* arg1;
		const char* arg2;
		const char* arg3;
		const char* arg4;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		std::string arg2_tmp; ok &= jsval_to_std_string(cx, argv[2], &arg2_tmp); arg2 = arg2_tmp.c_str();
		std::string arg3_tmp; ok &= jsval_to_std_string(cx, argv[3], &arg3_tmp); arg3 = arg3_tmp.c_str();
		std::string arg4_tmp; ok &= jsval_to_std_string(cx, argv[4], &arg4_tmp); arg4 = arg4_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_CheckBox_loadTextures : Error processing arguments");
		cobj->loadTextures(arg0, arg1, arg2, arg3, arg4);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 6) {
		const char* arg0;
		const char* arg1;
		const char* arg2;
		const char* arg3;
		const char* arg4;
		cocos2d::gui::TextureResType arg5;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		std::string arg2_tmp; ok &= jsval_to_std_string(cx, argv[2], &arg2_tmp); arg2 = arg2_tmp.c_str();
		std::string arg3_tmp; ok &= jsval_to_std_string(cx, argv[3], &arg3_tmp); arg3 = arg3_tmp.c_str();
		std::string arg4_tmp; ok &= jsval_to_std_string(cx, argv[4], &arg4_tmp); arg4 = arg4_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[5], (int32_t *)&arg5);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_CheckBox_loadTextures : Error processing arguments");
		cobj->loadTextures(arg0, arg1, arg2, arg3, arg4, arg5);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_CheckBox_loadTextures : wrong number of arguments: %d, was expecting %d", argc, 5);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_CheckBox_loadTextureBackGround(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::CheckBox* cobj = (cocos2d::gui::CheckBox *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_CheckBox_loadTextureBackGround : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_CheckBox_loadTextureBackGround : Error processing arguments");
		cobj->loadTextureBackGround(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 2) {
		const char* arg0;
		cocos2d::gui::TextureResType arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_CheckBox_loadTextureBackGround : Error processing arguments");
		cobj->loadTextureBackGround(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_CheckBox_loadTextureBackGround : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_CheckBox_setSelectedState(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::CheckBox* cobj = (cocos2d::gui::CheckBox *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_CheckBox_setSelectedState : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_CheckBox_setSelectedState : Error processing arguments");
		cobj->setSelectedState(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_CheckBox_setSelectedState : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_CheckBox_loadTextureFrontCrossDisabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::CheckBox* cobj = (cocos2d::gui::CheckBox *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_CheckBox_loadTextureFrontCrossDisabled : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_CheckBox_loadTextureFrontCrossDisabled : Error processing arguments");
		cobj->loadTextureFrontCrossDisabled(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 2) {
		const char* arg0;
		cocos2d::gui::TextureResType arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_CheckBox_loadTextureFrontCrossDisabled : Error processing arguments");
		cobj->loadTextureFrontCrossDisabled(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_CheckBox_loadTextureFrontCrossDisabled : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_CheckBox_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::CheckBox* ret = cocos2d::gui::CheckBox::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::CheckBox>(cx, (cocos2d::gui::CheckBox*)ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "js_cocos2dx_gui_CheckBox_create : wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_gui_CheckBox_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::CheckBox* cobj = new cocos2d::gui::CheckBox();
		cocos2d::Object *_ccobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::gui::CheckBox> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::gui::CheckBox");
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_CheckBox_constructor : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}


extern JSObject *jsb_cocos2d_gui_Widget_prototype;

void js_cocos2d_gui_CheckBox_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CheckBox)", obj);
}

void js_register_cocos2dx_gui_CheckBox(JSContext *cx, JSObject *global) {
	jsb_cocos2d_gui_CheckBox_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_gui_CheckBox_class->name = "CheckBox";
	jsb_cocos2d_gui_CheckBox_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_gui_CheckBox_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_gui_CheckBox_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_gui_CheckBox_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_gui_CheckBox_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_gui_CheckBox_class->resolve = JS_ResolveStub;
	jsb_cocos2d_gui_CheckBox_class->convert = JS_ConvertStub;
	jsb_cocos2d_gui_CheckBox_class->finalize = js_cocos2d_gui_CheckBox_finalize;
	jsb_cocos2d_gui_CheckBox_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getSelectedState", js_cocos2dx_gui_CheckBox_getSelectedState, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadTextureBackGroundSelected", js_cocos2dx_gui_CheckBox_loadTextureBackGroundSelected, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadTextureBackGroundDisabled", js_cocos2dx_gui_CheckBox_loadTextureBackGroundDisabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadTextureFrontCross", js_cocos2dx_gui_CheckBox_loadTextureFrontCross, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadTextures", js_cocos2dx_gui_CheckBox_loadTextures, 5, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadTextureBackGround", js_cocos2dx_gui_CheckBox_loadTextureBackGround, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setSelectedState", js_cocos2dx_gui_CheckBox_setSelectedState, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadTextureFrontCrossDisabled", js_cocos2dx_gui_CheckBox_loadTextureFrontCrossDisabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_gui_CheckBox_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_gui_CheckBox_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_gui_Widget_prototype,
		jsb_cocos2d_gui_CheckBox_class,
		js_cocos2dx_gui_CheckBox_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "CheckBox", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::gui::CheckBox> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_gui_CheckBox_class;
		p->proto = jsb_cocos2d_gui_CheckBox_prototype;
		p->parentProto = jsb_cocos2d_gui_Widget_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_gui_ImageView_class;
JSObject *jsb_cocos2d_gui_ImageView_prototype;

JSBool js_cocos2dx_gui_ImageView_setTextureRect(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ImageView* cobj = (cocos2d::gui::ImageView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ImageView_setTextureRect : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Rect arg0;
		ok &= jsval_to_ccrect(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ImageView_setTextureRect : Error processing arguments");
		cobj->setTextureRect(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ImageView_setTextureRect : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ImageView_setCapInsets(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ImageView* cobj = (cocos2d::gui::ImageView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ImageView_setCapInsets : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Rect arg0;
		ok &= jsval_to_ccrect(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ImageView_setCapInsets : Error processing arguments");
		cobj->setCapInsets(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ImageView_setCapInsets : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ImageView_setScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ImageView* cobj = (cocos2d::gui::ImageView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ImageView_setScale9Enabled : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ImageView_setScale9Enabled : Error processing arguments");
		cobj->setScale9Enabled(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ImageView_setScale9Enabled : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ImageView_loadTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ImageView* cobj = (cocos2d::gui::ImageView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ImageView_loadTexture : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ImageView_loadTexture : Error processing arguments");
		cobj->loadTexture(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 2) {
		const char* arg0;
		cocos2d::gui::TextureResType arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ImageView_loadTexture : Error processing arguments");
		cobj->loadTexture(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ImageView_loadTexture : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ImageView_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::ImageView* ret = cocos2d::gui::ImageView::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::ImageView>(cx, (cocos2d::gui::ImageView*)ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "js_cocos2dx_gui_ImageView_create : wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_gui_ImageView_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::ImageView* cobj = new cocos2d::gui::ImageView();
		cocos2d::Object *_ccobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::gui::ImageView> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::gui::ImageView");
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ImageView_constructor : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}


extern JSObject *jsb_cocos2d_gui_Widget_prototype;

void js_cocos2d_gui_ImageView_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ImageView)", obj);
}

void js_register_cocos2dx_gui_ImageView(JSContext *cx, JSObject *global) {
	jsb_cocos2d_gui_ImageView_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_gui_ImageView_class->name = "ImageView";
	jsb_cocos2d_gui_ImageView_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_gui_ImageView_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_gui_ImageView_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_gui_ImageView_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_gui_ImageView_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_gui_ImageView_class->resolve = JS_ResolveStub;
	jsb_cocos2d_gui_ImageView_class->convert = JS_ConvertStub;
	jsb_cocos2d_gui_ImageView_class->finalize = js_cocos2d_gui_ImageView_finalize;
	jsb_cocos2d_gui_ImageView_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("setTextureRect", js_cocos2dx_gui_ImageView_setTextureRect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCapInsets", js_cocos2dx_gui_ImageView_setCapInsets, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setScale9Enabled", js_cocos2dx_gui_ImageView_setScale9Enabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadTexture", js_cocos2dx_gui_ImageView_loadTexture, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_gui_ImageView_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_gui_ImageView_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_gui_Widget_prototype,
		jsb_cocos2d_gui_ImageView_class,
		js_cocos2dx_gui_ImageView_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ImageView", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::gui::ImageView> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_gui_ImageView_class;
		p->proto = jsb_cocos2d_gui_ImageView_prototype;
		p->parentProto = jsb_cocos2d_gui_Widget_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_gui_Text_class;
JSObject *jsb_cocos2d_gui_Text_prototype;

JSBool js_cocos2dx_gui_Text_getStringLength(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Text* cobj = (cocos2d::gui::Text *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Text_getStringLength : Invalid Native Object");
	if (argc == 0) {
		ssize_t ret = cobj->getStringLength();
		jsval jsret = JSVAL_NULL;
		jsret = ssize_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Text_getStringLength : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Text_setFontName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Text* cobj = (cocos2d::gui::Text *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Text_setFontName : Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Text_setFontName : Error processing arguments");
		cobj->setFontName(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Text_setFontName : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Text_setTouchScaleChangeEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Text* cobj = (cocos2d::gui::Text *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Text_setTouchScaleChangeEnabled : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Text_setTouchScaleChangeEnabled : Error processing arguments");
		cobj->setTouchScaleChangeEnabled(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Text_setTouchScaleChangeEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Text_getStringValue(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Text* cobj = (cocos2d::gui::Text *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Text_getStringValue : Invalid Native Object");
	if (argc == 0) {
		const std::string& ret = cobj->getStringValue();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Text_getStringValue : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Text_setText(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Text* cobj = (cocos2d::gui::Text *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Text_setText : Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Text_setText : Error processing arguments");
		cobj->setText(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Text_setText : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Text_setTextVerticalAlignment(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Text* cobj = (cocos2d::gui::Text *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Text_setTextVerticalAlignment : Invalid Native Object");
	if (argc == 1) {
		cocos2d::TextVAlignment arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Text_setTextVerticalAlignment : Error processing arguments");
		cobj->setTextVerticalAlignment(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Text_setTextVerticalAlignment : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Text_setFontSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Text* cobj = (cocos2d::gui::Text *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Text_setFontSize : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Text_setFontSize : Error processing arguments");
		cobj->setFontSize(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Text_setFontSize : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Text_isTouchScaleChangeEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Text* cobj = (cocos2d::gui::Text *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Text_isTouchScaleChangeEnabled : Invalid Native Object");
	if (argc == 0) {
		JSBool ret = cobj->isTouchScaleChangeEnabled();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Text_isTouchScaleChangeEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Text_setTextHorizontalAlignment(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Text* cobj = (cocos2d::gui::Text *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Text_setTextHorizontalAlignment : Invalid Native Object");
	if (argc == 1) {
		cocos2d::TextHAlignment arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Text_setTextHorizontalAlignment : Error processing arguments");
		cobj->setTextHorizontalAlignment(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Text_setTextHorizontalAlignment : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Text_setTextAreaSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Text* cobj = (cocos2d::gui::Text *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Text_setTextAreaSize : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Size arg0;
		ok &= jsval_to_ccsize(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Text_setTextAreaSize : Error processing arguments");
		cobj->setTextAreaSize(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Text_setTextAreaSize : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Text_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::Text* ret = cocos2d::gui::Text::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::Text>(cx, (cocos2d::gui::Text*)ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "js_cocos2dx_gui_Text_create : wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_gui_Text_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::Text* cobj = new cocos2d::gui::Text();
		cocos2d::Object *_ccobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::gui::Text> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::gui::Text");
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Text_constructor : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}


extern JSObject *jsb_cocos2d_gui_Widget_prototype;

void js_cocos2d_gui_Text_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Text)", obj);
}

void js_register_cocos2dx_gui_Text(JSContext *cx, JSObject *global) {
	jsb_cocos2d_gui_Text_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_gui_Text_class->name = "Text";
	jsb_cocos2d_gui_Text_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_gui_Text_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_gui_Text_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_gui_Text_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_gui_Text_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_gui_Text_class->resolve = JS_ResolveStub;
	jsb_cocos2d_gui_Text_class->convert = JS_ConvertStub;
	jsb_cocos2d_gui_Text_class->finalize = js_cocos2d_gui_Text_finalize;
	jsb_cocos2d_gui_Text_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getStringLength", js_cocos2dx_gui_Text_getStringLength, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setFontName", js_cocos2dx_gui_Text_setFontName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setTouchScaleChangeEnabled", js_cocos2dx_gui_Text_setTouchScaleChangeEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getStringValue", js_cocos2dx_gui_Text_getStringValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setText", js_cocos2dx_gui_Text_setText, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setTextVerticalAlignment", js_cocos2dx_gui_Text_setTextVerticalAlignment, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setFontSize", js_cocos2dx_gui_Text_setFontSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isTouchScaleChangeEnabled", js_cocos2dx_gui_Text_isTouchScaleChangeEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setTextHorizontalAlignment", js_cocos2dx_gui_Text_setTextHorizontalAlignment, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setTextAreaSize", js_cocos2dx_gui_Text_setTextAreaSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_gui_Text_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_gui_Text_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_gui_Widget_prototype,
		jsb_cocos2d_gui_Text_class,
		js_cocos2dx_gui_Text_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "Text", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::gui::Text> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_gui_Text_class;
		p->proto = jsb_cocos2d_gui_Text_prototype;
		p->parentProto = jsb_cocos2d_gui_Widget_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_gui_TextAtlas_class;
JSObject *jsb_cocos2d_gui_TextAtlas_prototype;

JSBool js_cocos2dx_gui_TextAtlas_setProperty(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextAtlas* cobj = (cocos2d::gui::TextAtlas *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextAtlas_setProperty : Invalid Native Object");
	if (argc == 5) {
		std::string arg0;
		std::string arg1;
		int arg2;
		int arg3;
		std::string arg4;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		ok &= jsval_to_std_string(cx, argv[1], &arg1);
		ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
		ok &= jsval_to_int32(cx, argv[3], (int32_t *)&arg3);
		ok &= jsval_to_std_string(cx, argv[4], &arg4);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_TextAtlas_setProperty : Error processing arguments");
		cobj->setProperty(arg0, arg1, arg2, arg3, arg4);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextAtlas_setProperty : wrong number of arguments: %d, was expecting %d", argc, 5);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextAtlas_getStringValue(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextAtlas* cobj = (cocos2d::gui::TextAtlas *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextAtlas_getStringValue : Invalid Native Object");
	if (argc == 0) {
		const std::string& ret = cobj->getStringValue();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextAtlas_getStringValue : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextAtlas_setStringValue(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextAtlas* cobj = (cocos2d::gui::TextAtlas *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextAtlas_setStringValue : Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_TextAtlas_setStringValue : Error processing arguments");
		cobj->setStringValue(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextAtlas_setStringValue : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextAtlas_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::TextAtlas* ret = cocos2d::gui::TextAtlas::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::TextAtlas>(cx, (cocos2d::gui::TextAtlas*)ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "js_cocos2dx_gui_TextAtlas_create : wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_gui_TextAtlas_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::TextAtlas* cobj = new cocos2d::gui::TextAtlas();
		cocos2d::Object *_ccobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::gui::TextAtlas> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::gui::TextAtlas");
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextAtlas_constructor : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}


extern JSObject *jsb_cocos2d_gui_Widget_prototype;

void js_cocos2d_gui_TextAtlas_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (TextAtlas)", obj);
}

void js_register_cocos2dx_gui_TextAtlas(JSContext *cx, JSObject *global) {
	jsb_cocos2d_gui_TextAtlas_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_gui_TextAtlas_class->name = "TextAtlas";
	jsb_cocos2d_gui_TextAtlas_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_gui_TextAtlas_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_gui_TextAtlas_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_gui_TextAtlas_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_gui_TextAtlas_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_gui_TextAtlas_class->resolve = JS_ResolveStub;
	jsb_cocos2d_gui_TextAtlas_class->convert = JS_ConvertStub;
	jsb_cocos2d_gui_TextAtlas_class->finalize = js_cocos2d_gui_TextAtlas_finalize;
	jsb_cocos2d_gui_TextAtlas_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("setProperty", js_cocos2dx_gui_TextAtlas_setProperty, 5, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getStringValue", js_cocos2dx_gui_TextAtlas_getStringValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setStringValue", js_cocos2dx_gui_TextAtlas_setStringValue, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_gui_TextAtlas_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_gui_TextAtlas_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_gui_Widget_prototype,
		jsb_cocos2d_gui_TextAtlas_class,
		js_cocos2dx_gui_TextAtlas_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "TextAtlas", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::gui::TextAtlas> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_gui_TextAtlas_class;
		p->proto = jsb_cocos2d_gui_TextAtlas_prototype;
		p->parentProto = jsb_cocos2d_gui_Widget_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_gui_LoadingBar_class;
JSObject *jsb_cocos2d_gui_LoadingBar_prototype;

JSBool js_cocos2dx_gui_LoadingBar_setPercent(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::LoadingBar* cobj = (cocos2d::gui::LoadingBar *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_LoadingBar_setPercent : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_LoadingBar_setPercent : Error processing arguments");
		cobj->setPercent(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_LoadingBar_setPercent : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_LoadingBar_loadTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::LoadingBar* cobj = (cocos2d::gui::LoadingBar *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_LoadingBar_loadTexture : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_LoadingBar_loadTexture : Error processing arguments");
		cobj->loadTexture(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 2) {
		const char* arg0;
		cocos2d::gui::TextureResType arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_LoadingBar_loadTexture : Error processing arguments");
		cobj->loadTexture(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_LoadingBar_loadTexture : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_LoadingBar_setDirection(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::LoadingBar* cobj = (cocos2d::gui::LoadingBar *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_LoadingBar_setDirection : Invalid Native Object");
	if (argc == 1) {
		cocos2d::gui::LoadingBarType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_LoadingBar_setDirection : Error processing arguments");
		cobj->setDirection(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_LoadingBar_setDirection : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_LoadingBar_setScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::LoadingBar* cobj = (cocos2d::gui::LoadingBar *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_LoadingBar_setScale9Enabled : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_LoadingBar_setScale9Enabled : Error processing arguments");
		cobj->setScale9Enabled(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_LoadingBar_setScale9Enabled : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_LoadingBar_setCapInsets(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::LoadingBar* cobj = (cocos2d::gui::LoadingBar *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_LoadingBar_setCapInsets : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Rect arg0;
		ok &= jsval_to_ccrect(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_LoadingBar_setCapInsets : Error processing arguments");
		cobj->setCapInsets(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_LoadingBar_setCapInsets : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_LoadingBar_getDirection(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::LoadingBar* cobj = (cocos2d::gui::LoadingBar *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_LoadingBar_getDirection : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getDirection();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_LoadingBar_getDirection : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_LoadingBar_getPercent(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::LoadingBar* cobj = (cocos2d::gui::LoadingBar *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_LoadingBar_getPercent : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getPercent();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_LoadingBar_getPercent : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_LoadingBar_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::LoadingBar* ret = cocos2d::gui::LoadingBar::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::LoadingBar>(cx, (cocos2d::gui::LoadingBar*)ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "js_cocos2dx_gui_LoadingBar_create : wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_gui_LoadingBar_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::LoadingBar* cobj = new cocos2d::gui::LoadingBar();
		cocos2d::Object *_ccobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::gui::LoadingBar> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::gui::LoadingBar");
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_LoadingBar_constructor : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}


extern JSObject *jsb_cocos2d_gui_Widget_prototype;

void js_cocos2d_gui_LoadingBar_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LoadingBar)", obj);
}

void js_register_cocos2dx_gui_LoadingBar(JSContext *cx, JSObject *global) {
	jsb_cocos2d_gui_LoadingBar_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_gui_LoadingBar_class->name = "LoadingBar";
	jsb_cocos2d_gui_LoadingBar_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_gui_LoadingBar_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_gui_LoadingBar_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_gui_LoadingBar_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_gui_LoadingBar_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_gui_LoadingBar_class->resolve = JS_ResolveStub;
	jsb_cocos2d_gui_LoadingBar_class->convert = JS_ConvertStub;
	jsb_cocos2d_gui_LoadingBar_class->finalize = js_cocos2d_gui_LoadingBar_finalize;
	jsb_cocos2d_gui_LoadingBar_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("setPercent", js_cocos2dx_gui_LoadingBar_setPercent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadTexture", js_cocos2dx_gui_LoadingBar_loadTexture, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setDirection", js_cocos2dx_gui_LoadingBar_setDirection, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setScale9Enabled", js_cocos2dx_gui_LoadingBar_setScale9Enabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCapInsets", js_cocos2dx_gui_LoadingBar_setCapInsets, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getDirection", js_cocos2dx_gui_LoadingBar_getDirection, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPercent", js_cocos2dx_gui_LoadingBar_getPercent, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_gui_LoadingBar_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_gui_LoadingBar_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_gui_Widget_prototype,
		jsb_cocos2d_gui_LoadingBar_class,
		js_cocos2dx_gui_LoadingBar_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "LoadingBar", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::gui::LoadingBar> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_gui_LoadingBar_class;
		p->proto = jsb_cocos2d_gui_LoadingBar_prototype;
		p->parentProto = jsb_cocos2d_gui_Widget_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_gui_ScrollView_class;
JSObject *jsb_cocos2d_gui_ScrollView_prototype;

JSBool js_cocos2dx_gui_ScrollView_scrollToTop(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToTop : Invalid Native Object");
	if (argc == 2) {
		double arg0;
		JSBool arg1;
		ok &= JS_ValueToNumber(cx, argv[0], &arg0);
		ok &= JS_ValueToBoolean(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToTop : Error processing arguments");
		cobj->scrollToTop(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_scrollToTop : wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_scrollToPercentHorizontal(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToPercentHorizontal : Invalid Native Object");
	if (argc == 3) {
		double arg0;
		double arg1;
		JSBool arg2;
		ok &= JS_ValueToNumber(cx, argv[0], &arg0);
		ok &= JS_ValueToNumber(cx, argv[1], &arg1);
		ok &= JS_ValueToBoolean(cx, argv[2], &arg2);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToPercentHorizontal : Error processing arguments");
		cobj->scrollToPercentHorizontal(arg0, arg1, arg2);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_scrollToPercentHorizontal : wrong number of arguments: %d, was expecting %d", argc, 3);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_isInertiaScrollEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_isInertiaScrollEnabled : Invalid Native Object");
	if (argc == 0) {
		JSBool ret = cobj->isInertiaScrollEnabled();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_isInertiaScrollEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_scrollToPercentBothDirection(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToPercentBothDirection : Invalid Native Object");
	if (argc == 3) {
		cocos2d::Point arg0;
		double arg1;
		JSBool arg2;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		ok &= JS_ValueToNumber(cx, argv[1], &arg1);
		ok &= JS_ValueToBoolean(cx, argv[2], &arg2);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToPercentBothDirection : Error processing arguments");
		cobj->scrollToPercentBothDirection(arg0, arg1, arg2);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_scrollToPercentBothDirection : wrong number of arguments: %d, was expecting %d", argc, 3);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_getDirection(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_getDirection : Invalid Native Object");
	if (argc == 0) {
		int ret = (int)cobj->getDirection();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_getDirection : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_scrollToBottomLeft(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToBottomLeft : Invalid Native Object");
	if (argc == 2) {
		double arg0;
		JSBool arg1;
		ok &= JS_ValueToNumber(cx, argv[0], &arg0);
		ok &= JS_ValueToBoolean(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToBottomLeft : Error processing arguments");
		cobj->scrollToBottomLeft(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_scrollToBottomLeft : wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_getInnerContainer(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_getInnerContainer : Invalid Native Object");
	if (argc == 0) {
		cocos2d::gui::Layout* ret = cobj->getInnerContainer();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::Layout>(cx, (cocos2d::gui::Layout*)ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_getInnerContainer : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_jumpToBottom(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_jumpToBottom : Invalid Native Object");
	if (argc == 0) {
		cobj->jumpToBottom();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_jumpToBottom : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_setDirection(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_setDirection : Invalid Native Object");
	if (argc == 1) {
		cocos2d::gui::SCROLLVIEW_DIR arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_setDirection : Error processing arguments");
		cobj->setDirection(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_setDirection : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_scrollToTopLeft(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToTopLeft : Invalid Native Object");
	if (argc == 2) {
		double arg0;
		JSBool arg1;
		ok &= JS_ValueToNumber(cx, argv[0], &arg0);
		ok &= JS_ValueToBoolean(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToTopLeft : Error processing arguments");
		cobj->scrollToTopLeft(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_scrollToTopLeft : wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_jumpToTopRight(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_jumpToTopRight : Invalid Native Object");
	if (argc == 0) {
		cobj->jumpToTopRight();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_jumpToTopRight : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_jumpToBottomLeft(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_jumpToBottomLeft : Invalid Native Object");
	if (argc == 0) {
		cobj->jumpToBottomLeft();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_jumpToBottomLeft : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_setInnerContainerSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_setInnerContainerSize : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Size arg0;
		ok &= jsval_to_ccsize(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_setInnerContainerSize : Error processing arguments");
		cobj->setInnerContainerSize(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_setInnerContainerSize : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_getInnerContainerSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_getInnerContainerSize : Invalid Native Object");
	if (argc == 0) {
		const cocos2d::Size& ret = cobj->getInnerContainerSize();
		jsval jsret = JSVAL_NULL;
		jsret = ccsize_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_getInnerContainerSize : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_isBounceEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_isBounceEnabled : Invalid Native Object");
	if (argc == 0) {
		JSBool ret = cobj->isBounceEnabled();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_isBounceEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_jumpToPercentVertical(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_jumpToPercentVertical : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS_ValueToNumber(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_jumpToPercentVertical : Error processing arguments");
		cobj->jumpToPercentVertical(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_jumpToPercentVertical : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_setInertiaScrollEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_setInertiaScrollEnabled : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_setInertiaScrollEnabled : Error processing arguments");
		cobj->setInertiaScrollEnabled(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_setInertiaScrollEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_jumpToTopLeft(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_jumpToTopLeft : Invalid Native Object");
	if (argc == 0) {
		cobj->jumpToTopLeft();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_jumpToTopLeft : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_jumpToPercentHorizontal(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_jumpToPercentHorizontal : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS_ValueToNumber(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_jumpToPercentHorizontal : Error processing arguments");
		cobj->jumpToPercentHorizontal(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_jumpToPercentHorizontal : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_jumpToBottomRight(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_jumpToBottomRight : Invalid Native Object");
	if (argc == 0) {
		cobj->jumpToBottomRight();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_jumpToBottomRight : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_setBounceEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_setBounceEnabled : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_setBounceEnabled : Error processing arguments");
		cobj->setBounceEnabled(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_setBounceEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_jumpToTop(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_jumpToTop : Invalid Native Object");
	if (argc == 0) {
		cobj->jumpToTop();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_jumpToTop : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_scrollToLeft(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToLeft : Invalid Native Object");
	if (argc == 2) {
		double arg0;
		JSBool arg1;
		ok &= JS_ValueToNumber(cx, argv[0], &arg0);
		ok &= JS_ValueToBoolean(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToLeft : Error processing arguments");
		cobj->scrollToLeft(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_scrollToLeft : wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_jumpToPercentBothDirection(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_jumpToPercentBothDirection : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_jumpToPercentBothDirection : Error processing arguments");
		cobj->jumpToPercentBothDirection(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_jumpToPercentBothDirection : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_scrollToPercentVertical(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToPercentVertical : Invalid Native Object");
	if (argc == 3) {
		double arg0;
		double arg1;
		JSBool arg2;
		ok &= JS_ValueToNumber(cx, argv[0], &arg0);
		ok &= JS_ValueToNumber(cx, argv[1], &arg1);
		ok &= JS_ValueToBoolean(cx, argv[2], &arg2);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToPercentVertical : Error processing arguments");
		cobj->scrollToPercentVertical(arg0, arg1, arg2);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_scrollToPercentVertical : wrong number of arguments: %d, was expecting %d", argc, 3);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_scrollToBottom(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToBottom : Invalid Native Object");
	if (argc == 2) {
		double arg0;
		JSBool arg1;
		ok &= JS_ValueToNumber(cx, argv[0], &arg0);
		ok &= JS_ValueToBoolean(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToBottom : Error processing arguments");
		cobj->scrollToBottom(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_scrollToBottom : wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_scrollToBottomRight(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToBottomRight : Invalid Native Object");
	if (argc == 2) {
		double arg0;
		JSBool arg1;
		ok &= JS_ValueToNumber(cx, argv[0], &arg0);
		ok &= JS_ValueToBoolean(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToBottomRight : Error processing arguments");
		cobj->scrollToBottomRight(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_scrollToBottomRight : wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_jumpToLeft(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_jumpToLeft : Invalid Native Object");
	if (argc == 0) {
		cobj->jumpToLeft();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_jumpToLeft : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_scrollToRight(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToRight : Invalid Native Object");
	if (argc == 2) {
		double arg0;
		JSBool arg1;
		ok &= JS_ValueToNumber(cx, argv[0], &arg0);
		ok &= JS_ValueToBoolean(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToRight : Error processing arguments");
		cobj->scrollToRight(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_scrollToRight : wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_jumpToRight(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_jumpToRight : Invalid Native Object");
	if (argc == 0) {
		cobj->jumpToRight();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_jumpToRight : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_scrollToTopRight(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ScrollView* cobj = (cocos2d::gui::ScrollView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToTopRight : Invalid Native Object");
	if (argc == 2) {
		double arg0;
		JSBool arg1;
		ok &= JS_ValueToNumber(cx, argv[0], &arg0);
		ok &= JS_ValueToBoolean(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ScrollView_scrollToTopRight : Error processing arguments");
		cobj->scrollToTopRight(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_scrollToTopRight : wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ScrollView_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::ScrollView* ret = cocos2d::gui::ScrollView::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::ScrollView>(cx, (cocos2d::gui::ScrollView*)ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_create : wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_gui_ScrollView_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::ScrollView* cobj = new cocos2d::gui::ScrollView();
		cocos2d::Object *_ccobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::gui::ScrollView> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::gui::ScrollView");
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ScrollView_constructor : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}


extern JSObject *jsb_cocos2d_gui_Layout_prototype;

void js_cocos2d_gui_ScrollView_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ScrollView)", obj);
}

void js_register_cocos2dx_gui_ScrollView(JSContext *cx, JSObject *global) {
	jsb_cocos2d_gui_ScrollView_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_gui_ScrollView_class->name = "ScrollView";
	jsb_cocos2d_gui_ScrollView_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_gui_ScrollView_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_gui_ScrollView_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_gui_ScrollView_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_gui_ScrollView_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_gui_ScrollView_class->resolve = JS_ResolveStub;
	jsb_cocos2d_gui_ScrollView_class->convert = JS_ConvertStub;
	jsb_cocos2d_gui_ScrollView_class->finalize = js_cocos2d_gui_ScrollView_finalize;
	jsb_cocos2d_gui_ScrollView_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("scrollToTop", js_cocos2dx_gui_ScrollView_scrollToTop, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("scrollToPercentHorizontal", js_cocos2dx_gui_ScrollView_scrollToPercentHorizontal, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isInertiaScrollEnabled", js_cocos2dx_gui_ScrollView_isInertiaScrollEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("scrollToPercentBothDirection", js_cocos2dx_gui_ScrollView_scrollToPercentBothDirection, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getDirection", js_cocos2dx_gui_ScrollView_getDirection, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("scrollToBottomLeft", js_cocos2dx_gui_ScrollView_scrollToBottomLeft, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getInnerContainer", js_cocos2dx_gui_ScrollView_getInnerContainer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("jumpToBottom", js_cocos2dx_gui_ScrollView_jumpToBottom, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setDirection", js_cocos2dx_gui_ScrollView_setDirection, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("scrollToTopLeft", js_cocos2dx_gui_ScrollView_scrollToTopLeft, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("jumpToTopRight", js_cocos2dx_gui_ScrollView_jumpToTopRight, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("jumpToBottomLeft", js_cocos2dx_gui_ScrollView_jumpToBottomLeft, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setInnerContainerSize", js_cocos2dx_gui_ScrollView_setInnerContainerSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getInnerContainerSize", js_cocos2dx_gui_ScrollView_getInnerContainerSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isBounceEnabled", js_cocos2dx_gui_ScrollView_isBounceEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("jumpToPercentVertical", js_cocos2dx_gui_ScrollView_jumpToPercentVertical, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setInertiaScrollEnabled", js_cocos2dx_gui_ScrollView_setInertiaScrollEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("jumpToTopLeft", js_cocos2dx_gui_ScrollView_jumpToTopLeft, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("jumpToPercentHorizontal", js_cocos2dx_gui_ScrollView_jumpToPercentHorizontal, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("jumpToBottomRight", js_cocos2dx_gui_ScrollView_jumpToBottomRight, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setBounceEnabled", js_cocos2dx_gui_ScrollView_setBounceEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("jumpToTop", js_cocos2dx_gui_ScrollView_jumpToTop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("scrollToLeft", js_cocos2dx_gui_ScrollView_scrollToLeft, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("jumpToPercentBothDirection", js_cocos2dx_gui_ScrollView_jumpToPercentBothDirection, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("scrollToPercentVertical", js_cocos2dx_gui_ScrollView_scrollToPercentVertical, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("scrollToBottom", js_cocos2dx_gui_ScrollView_scrollToBottom, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("scrollToBottomRight", js_cocos2dx_gui_ScrollView_scrollToBottomRight, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("jumpToLeft", js_cocos2dx_gui_ScrollView_jumpToLeft, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("scrollToRight", js_cocos2dx_gui_ScrollView_scrollToRight, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("jumpToRight", js_cocos2dx_gui_ScrollView_jumpToRight, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("scrollToTopRight", js_cocos2dx_gui_ScrollView_scrollToTopRight, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_gui_ScrollView_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_gui_ScrollView_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_gui_Layout_prototype,
		jsb_cocos2d_gui_ScrollView_class,
		js_cocos2dx_gui_ScrollView_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ScrollView", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::gui::ScrollView> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_gui_ScrollView_class;
		p->proto = jsb_cocos2d_gui_ScrollView_prototype;
		p->parentProto = jsb_cocos2d_gui_Layout_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_gui_ListView_class;
JSObject *jsb_cocos2d_gui_ListView_prototype;

JSBool js_cocos2dx_gui_ListView_getIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ListView* cobj = (cocos2d::gui::ListView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ListView_getIndex : Invalid Native Object");
	if (argc == 1) {
		cocos2d::gui::Widget* arg0;
		do {
			if (!argv[0].isObject()) { ok = JS_FALSE; break; }
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::gui::Widget*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ListView_getIndex : Error processing arguments");
		ssize_t ret = cobj->getIndex(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = ssize_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ListView_getIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ListView_removeAllItems(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ListView* cobj = (cocos2d::gui::ListView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ListView_removeAllItems : Invalid Native Object");
	if (argc == 0) {
		cobj->removeAllItems();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ListView_removeAllItems : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ListView_setGravity(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ListView* cobj = (cocos2d::gui::ListView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ListView_setGravity : Invalid Native Object");
	if (argc == 1) {
		cocos2d::gui::ListViewGravity arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ListView_setGravity : Error processing arguments");
		cobj->setGravity(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ListView_setGravity : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ListView_pushBackCustomItem(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ListView* cobj = (cocos2d::gui::ListView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ListView_pushBackCustomItem : Invalid Native Object");
	if (argc == 1) {
		cocos2d::gui::Widget* arg0;
		do {
			if (!argv[0].isObject()) { ok = JS_FALSE; break; }
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::gui::Widget*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ListView_pushBackCustomItem : Error processing arguments");
		cobj->pushBackCustomItem(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ListView_pushBackCustomItem : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ListView_getItems(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ListView* cobj = (cocos2d::gui::ListView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ListView_getItems : Invalid Native Object");
	if (argc == 0) {
		cocos2d::Vector<cocos2d::gui::Widget *>& ret = cobj->getItems();
		jsval jsret = JSVAL_NULL;
		jsret = ccvector_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ListView_getItems : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ListView_removeItem(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ListView* cobj = (cocos2d::gui::ListView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ListView_removeItem : Invalid Native Object");
	if (argc == 1) {
		ssize_t arg0;
		ok &= jsval_to_ssize(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ListView_removeItem : Error processing arguments");
		cobj->removeItem(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ListView_removeItem : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ListView_getCurSelectedIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ListView* cobj = (cocos2d::gui::ListView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ListView_getCurSelectedIndex : Invalid Native Object");
	if (argc == 0) {
		ssize_t ret = cobj->getCurSelectedIndex();
		jsval jsret = JSVAL_NULL;
		jsret = ssize_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ListView_getCurSelectedIndex : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ListView_insertDefaultItem(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ListView* cobj = (cocos2d::gui::ListView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ListView_insertDefaultItem : Invalid Native Object");
	if (argc == 1) {
		ssize_t arg0;
		ok &= jsval_to_ssize(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ListView_insertDefaultItem : Error processing arguments");
		cobj->insertDefaultItem(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ListView_insertDefaultItem : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ListView_setItemsMargin(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ListView* cobj = (cocos2d::gui::ListView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ListView_setItemsMargin : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS_ValueToNumber(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ListView_setItemsMargin : Error processing arguments");
		cobj->setItemsMargin(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ListView_setItemsMargin : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ListView_removeLastItem(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ListView* cobj = (cocos2d::gui::ListView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ListView_removeLastItem : Invalid Native Object");
	if (argc == 0) {
		cobj->removeLastItem();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ListView_removeLastItem : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ListView_getItem(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ListView* cobj = (cocos2d::gui::ListView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ListView_getItem : Invalid Native Object");
	if (argc == 1) {
		ssize_t arg0;
		ok &= jsval_to_ssize(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ListView_getItem : Error processing arguments");
		cocos2d::gui::Widget* ret = cobj->getItem(arg0);
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::Widget>(cx, (cocos2d::gui::Widget*)ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ListView_getItem : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ListView_setItemModel(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ListView* cobj = (cocos2d::gui::ListView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ListView_setItemModel : Invalid Native Object");
	if (argc == 1) {
		cocos2d::gui::Widget* arg0;
		do {
			if (!argv[0].isObject()) { ok = JS_FALSE; break; }
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::gui::Widget*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ListView_setItemModel : Error processing arguments");
		cobj->setItemModel(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ListView_setItemModel : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ListView_requestRefreshView(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ListView* cobj = (cocos2d::gui::ListView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ListView_requestRefreshView : Invalid Native Object");
	if (argc == 0) {
		cobj->requestRefreshView();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ListView_requestRefreshView : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ListView_pushBackDefaultItem(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ListView* cobj = (cocos2d::gui::ListView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ListView_pushBackDefaultItem : Invalid Native Object");
	if (argc == 0) {
		cobj->pushBackDefaultItem();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ListView_pushBackDefaultItem : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ListView_insertCustomItem(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::ListView* cobj = (cocos2d::gui::ListView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_ListView_insertCustomItem : Invalid Native Object");
	if (argc == 2) {
		cocos2d::gui::Widget* arg0;
		ssize_t arg1;
		do {
			if (!argv[0].isObject()) { ok = JS_FALSE; break; }
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::gui::Widget*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		ok &= jsval_to_ssize(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_ListView_insertCustomItem : Error processing arguments");
		cobj->insertCustomItem(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ListView_insertCustomItem : wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_ListView_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::ListView* ret = cocos2d::gui::ListView::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::ListView>(cx, (cocos2d::gui::ListView*)ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "js_cocos2dx_gui_ListView_create : wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_gui_ListView_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::ListView* cobj = new cocos2d::gui::ListView();
		cocos2d::Object *_ccobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::gui::ListView> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::gui::ListView");
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_ListView_constructor : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}


extern JSObject *jsb_cocos2d_gui_ScrollView_prototype;

void js_cocos2d_gui_ListView_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ListView)", obj);
}

void js_register_cocos2dx_gui_ListView(JSContext *cx, JSObject *global) {
	jsb_cocos2d_gui_ListView_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_gui_ListView_class->name = "ListView";
	jsb_cocos2d_gui_ListView_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_gui_ListView_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_gui_ListView_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_gui_ListView_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_gui_ListView_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_gui_ListView_class->resolve = JS_ResolveStub;
	jsb_cocos2d_gui_ListView_class->convert = JS_ConvertStub;
	jsb_cocos2d_gui_ListView_class->finalize = js_cocos2d_gui_ListView_finalize;
	jsb_cocos2d_gui_ListView_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getIndex", js_cocos2dx_gui_ListView_getIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("removeAllItems", js_cocos2dx_gui_ListView_removeAllItems, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setGravity", js_cocos2dx_gui_ListView_setGravity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("pushBackCustomItem", js_cocos2dx_gui_ListView_pushBackCustomItem, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getItems", js_cocos2dx_gui_ListView_getItems, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("removeItem", js_cocos2dx_gui_ListView_removeItem, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getCurSelectedIndex", js_cocos2dx_gui_ListView_getCurSelectedIndex, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("insertDefaultItem", js_cocos2dx_gui_ListView_insertDefaultItem, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setItemsMargin", js_cocos2dx_gui_ListView_setItemsMargin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("removeLastItem", js_cocos2dx_gui_ListView_removeLastItem, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getItem", js_cocos2dx_gui_ListView_getItem, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setItemModel", js_cocos2dx_gui_ListView_setItemModel, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("requestRefreshView", js_cocos2dx_gui_ListView_requestRefreshView, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("pushBackDefaultItem", js_cocos2dx_gui_ListView_pushBackDefaultItem, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("insertCustomItem", js_cocos2dx_gui_ListView_insertCustomItem, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_gui_ListView_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_gui_ListView_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_gui_ScrollView_prototype,
		jsb_cocos2d_gui_ListView_class,
		js_cocos2dx_gui_ListView_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ListView", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::gui::ListView> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_gui_ListView_class;
		p->proto = jsb_cocos2d_gui_ListView_prototype;
		p->parentProto = jsb_cocos2d_gui_ScrollView_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_gui_Slider_class;
JSObject *jsb_cocos2d_gui_Slider_prototype;

JSBool js_cocos2dx_gui_Slider_setPercent(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Slider* cobj = (cocos2d::gui::Slider *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Slider_setPercent : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Slider_setPercent : Error processing arguments");
		cobj->setPercent(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Slider_setPercent : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Slider_loadSlidBallTextureNormal(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Slider* cobj = (cocos2d::gui::Slider *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Slider_loadSlidBallTextureNormal : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Slider_loadSlidBallTextureNormal : Error processing arguments");
		cobj->loadSlidBallTextureNormal(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 2) {
		const char* arg0;
		cocos2d::gui::TextureResType arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Slider_loadSlidBallTextureNormal : Error processing arguments");
		cobj->loadSlidBallTextureNormal(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Slider_loadSlidBallTextureNormal : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Slider_loadBarTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Slider* cobj = (cocos2d::gui::Slider *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Slider_loadBarTexture : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Slider_loadBarTexture : Error processing arguments");
		cobj->loadBarTexture(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 2) {
		const char* arg0;
		cocos2d::gui::TextureResType arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Slider_loadBarTexture : Error processing arguments");
		cobj->loadBarTexture(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Slider_loadBarTexture : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Slider_loadProgressBarTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Slider* cobj = (cocos2d::gui::Slider *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Slider_loadProgressBarTexture : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Slider_loadProgressBarTexture : Error processing arguments");
		cobj->loadProgressBarTexture(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 2) {
		const char* arg0;
		cocos2d::gui::TextureResType arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Slider_loadProgressBarTexture : Error processing arguments");
		cobj->loadProgressBarTexture(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Slider_loadProgressBarTexture : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Slider_loadSlidBallTextures(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Slider* cobj = (cocos2d::gui::Slider *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Slider_loadSlidBallTextures : Invalid Native Object");
	if (argc == 3) {
		const char* arg0;
		const char* arg1;
		const char* arg2;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		std::string arg2_tmp; ok &= jsval_to_std_string(cx, argv[2], &arg2_tmp); arg2 = arg2_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Slider_loadSlidBallTextures : Error processing arguments");
		cobj->loadSlidBallTextures(arg0, arg1, arg2);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 4) {
		const char* arg0;
		const char* arg1;
		const char* arg2;
		cocos2d::gui::TextureResType arg3;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		std::string arg2_tmp; ok &= jsval_to_std_string(cx, argv[2], &arg2_tmp); arg2 = arg2_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[3], (int32_t *)&arg3);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Slider_loadSlidBallTextures : Error processing arguments");
		cobj->loadSlidBallTextures(arg0, arg1, arg2, arg3);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Slider_loadSlidBallTextures : wrong number of arguments: %d, was expecting %d", argc, 3);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Slider_setCapInsetProgressBarRebderer(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Slider* cobj = (cocos2d::gui::Slider *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Slider_setCapInsetProgressBarRebderer : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Rect arg0;
		ok &= jsval_to_ccrect(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Slider_setCapInsetProgressBarRebderer : Error processing arguments");
		cobj->setCapInsetProgressBarRebderer(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Slider_setCapInsetProgressBarRebderer : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Slider_setCapInsetsBarRenderer(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Slider* cobj = (cocos2d::gui::Slider *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Slider_setCapInsetsBarRenderer : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Rect arg0;
		ok &= jsval_to_ccrect(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Slider_setCapInsetsBarRenderer : Error processing arguments");
		cobj->setCapInsetsBarRenderer(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Slider_setCapInsetsBarRenderer : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Slider_setScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Slider* cobj = (cocos2d::gui::Slider *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Slider_setScale9Enabled : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Slider_setScale9Enabled : Error processing arguments");
		cobj->setScale9Enabled(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Slider_setScale9Enabled : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Slider_setCapInsets(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Slider* cobj = (cocos2d::gui::Slider *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Slider_setCapInsets : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Rect arg0;
		ok &= jsval_to_ccrect(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Slider_setCapInsets : Error processing arguments");
		cobj->setCapInsets(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Slider_setCapInsets : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Slider_loadSlidBallTexturePressed(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Slider* cobj = (cocos2d::gui::Slider *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Slider_loadSlidBallTexturePressed : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Slider_loadSlidBallTexturePressed : Error processing arguments");
		cobj->loadSlidBallTexturePressed(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 2) {
		const char* arg0;
		cocos2d::gui::TextureResType arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Slider_loadSlidBallTexturePressed : Error processing arguments");
		cobj->loadSlidBallTexturePressed(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Slider_loadSlidBallTexturePressed : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Slider_loadSlidBallTextureDisabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Slider* cobj = (cocos2d::gui::Slider *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Slider_loadSlidBallTextureDisabled : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Slider_loadSlidBallTextureDisabled : Error processing arguments");
		cobj->loadSlidBallTextureDisabled(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 2) {
		const char* arg0;
		cocos2d::gui::TextureResType arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Slider_loadSlidBallTextureDisabled : Error processing arguments");
		cobj->loadSlidBallTextureDisabled(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Slider_loadSlidBallTextureDisabled : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Slider_getPercent(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::Slider* cobj = (cocos2d::gui::Slider *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_Slider_getPercent : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getPercent();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Slider_getPercent : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_Slider_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::Slider* ret = cocos2d::gui::Slider::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::Slider>(cx, (cocos2d::gui::Slider*)ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "js_cocos2dx_gui_Slider_create : wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_gui_Slider_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::Slider* cobj = new cocos2d::gui::Slider();
		cocos2d::Object *_ccobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::gui::Slider> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::gui::Slider");
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_Slider_constructor : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}


extern JSObject *jsb_cocos2d_gui_Widget_prototype;

void js_cocos2d_gui_Slider_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Slider)", obj);
}

void js_register_cocos2dx_gui_Slider(JSContext *cx, JSObject *global) {
	jsb_cocos2d_gui_Slider_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_gui_Slider_class->name = "Slider";
	jsb_cocos2d_gui_Slider_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_gui_Slider_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_gui_Slider_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_gui_Slider_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_gui_Slider_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_gui_Slider_class->resolve = JS_ResolveStub;
	jsb_cocos2d_gui_Slider_class->convert = JS_ConvertStub;
	jsb_cocos2d_gui_Slider_class->finalize = js_cocos2d_gui_Slider_finalize;
	jsb_cocos2d_gui_Slider_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("setPercent", js_cocos2dx_gui_Slider_setPercent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadSlidBallTextureNormal", js_cocos2dx_gui_Slider_loadSlidBallTextureNormal, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadBarTexture", js_cocos2dx_gui_Slider_loadBarTexture, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadProgressBarTexture", js_cocos2dx_gui_Slider_loadProgressBarTexture, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadSlidBallTextures", js_cocos2dx_gui_Slider_loadSlidBallTextures, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCapInsetProgressBarRebderer", js_cocos2dx_gui_Slider_setCapInsetProgressBarRebderer, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCapInsetsBarRenderer", js_cocos2dx_gui_Slider_setCapInsetsBarRenderer, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setScale9Enabled", js_cocos2dx_gui_Slider_setScale9Enabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCapInsets", js_cocos2dx_gui_Slider_setCapInsets, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadSlidBallTexturePressed", js_cocos2dx_gui_Slider_loadSlidBallTexturePressed, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadSlidBallTextureDisabled", js_cocos2dx_gui_Slider_loadSlidBallTextureDisabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPercent", js_cocos2dx_gui_Slider_getPercent, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_gui_Slider_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_gui_Slider_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_gui_Widget_prototype,
		jsb_cocos2d_gui_Slider_class,
		js_cocos2dx_gui_Slider_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "Slider", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::gui::Slider> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_gui_Slider_class;
		p->proto = jsb_cocos2d_gui_Slider_prototype;
		p->parentProto = jsb_cocos2d_gui_Widget_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_gui_TextField_class;
JSObject *jsb_cocos2d_gui_TextField_prototype;

JSBool js_cocos2dx_gui_TextField_setAttachWithIME(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setAttachWithIME : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setAttachWithIME : Error processing arguments");
		cobj->setAttachWithIME(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_setAttachWithIME : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_getStringValue(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_getStringValue : Invalid Native Object");
	if (argc == 0) {
		const std::string& ret = cobj->getStringValue();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_getStringValue : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_setPasswordStyleText(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setPasswordStyleText : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setPasswordStyleText : Error processing arguments");
		cobj->setPasswordStyleText(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_setPasswordStyleText : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_getAttachWithIME(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_getAttachWithIME : Invalid Native Object");
	if (argc == 0) {
		JSBool ret = cobj->getAttachWithIME();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_getAttachWithIME : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_setFontName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setFontName : Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setFontName : Error processing arguments");
		cobj->setFontName(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_setFontName : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_getInsertText(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_getInsertText : Invalid Native Object");
	if (argc == 0) {
		JSBool ret = cobj->getInsertText();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_getInsertText : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_setInsertText(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setInsertText : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setInsertText : Error processing arguments");
		cobj->setInsertText(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_setInsertText : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_getDetachWithIME(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_getDetachWithIME : Invalid Native Object");
	if (argc == 0) {
		JSBool ret = cobj->getDetachWithIME();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_getDetachWithIME : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_didNotSelectSelf(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_didNotSelectSelf : Invalid Native Object");
	if (argc == 0) {
		cobj->didNotSelectSelf();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_didNotSelectSelf : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_attachWithIME(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_attachWithIME : Invalid Native Object");
	if (argc == 0) {
		cobj->attachWithIME();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_attachWithIME : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_setPasswordEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setPasswordEnabled : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setPasswordEnabled : Error processing arguments");
		cobj->setPasswordEnabled(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_setPasswordEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_setMaxLengthEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setMaxLengthEnabled : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setMaxLengthEnabled : Error processing arguments");
		cobj->setMaxLengthEnabled(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_setMaxLengthEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_getDeleteBackward(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_getDeleteBackward : Invalid Native Object");
	if (argc == 0) {
		JSBool ret = cobj->getDeleteBackward();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_getDeleteBackward : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_setFontSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setFontSize : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setFontSize : Error processing arguments");
		cobj->setFontSize(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_setFontSize : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_setPlaceHolder(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setPlaceHolder : Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setPlaceHolder : Error processing arguments");
		cobj->setPlaceHolder(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_setPlaceHolder : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_isPasswordEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_isPasswordEnabled : Invalid Native Object");
	if (argc == 0) {
		JSBool ret = cobj->isPasswordEnabled();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_isPasswordEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_getMaxLength(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_getMaxLength : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getMaxLength();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_getMaxLength : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_isMaxLengthEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_isMaxLengthEnabled : Invalid Native Object");
	if (argc == 0) {
		JSBool ret = cobj->isMaxLengthEnabled();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_isMaxLengthEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_setDetachWithIME(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setDetachWithIME : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setDetachWithIME : Error processing arguments");
		cobj->setDetachWithIME(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_setDetachWithIME : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_setText(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setText : Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setText : Error processing arguments");
		cobj->setText(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_setText : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_setMaxLength(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setMaxLength : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setMaxLength : Error processing arguments");
		cobj->setMaxLength(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_setMaxLength : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_setTouchSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setTouchSize : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Size arg0;
		ok &= jsval_to_ccsize(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setTouchSize : Error processing arguments");
		cobj->setTouchSize(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_setTouchSize : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_setDeleteBackward(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextField* cobj = (cocos2d::gui::TextField *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setDeleteBackward : Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_TextField_setDeleteBackward : Error processing arguments");
		cobj->setDeleteBackward(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_setDeleteBackward : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextField_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::TextField* ret = cocos2d::gui::TextField::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::TextField>(cx, (cocos2d::gui::TextField*)ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "js_cocos2dx_gui_TextField_create : wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_gui_TextField_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::TextField* cobj = new cocos2d::gui::TextField();
		cocos2d::Object *_ccobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::gui::TextField> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::gui::TextField");
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextField_constructor : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}


extern JSObject *jsb_cocos2d_gui_Widget_prototype;

void js_cocos2d_gui_TextField_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (TextField)", obj);
}

void js_register_cocos2dx_gui_TextField(JSContext *cx, JSObject *global) {
	jsb_cocos2d_gui_TextField_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_gui_TextField_class->name = "TextField";
	jsb_cocos2d_gui_TextField_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_gui_TextField_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_gui_TextField_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_gui_TextField_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_gui_TextField_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_gui_TextField_class->resolve = JS_ResolveStub;
	jsb_cocos2d_gui_TextField_class->convert = JS_ConvertStub;
	jsb_cocos2d_gui_TextField_class->finalize = js_cocos2d_gui_TextField_finalize;
	jsb_cocos2d_gui_TextField_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("setAttachWithIME", js_cocos2dx_gui_TextField_setAttachWithIME, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getStringValue", js_cocos2dx_gui_TextField_getStringValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setPasswordStyleText", js_cocos2dx_gui_TextField_setPasswordStyleText, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getAttachWithIME", js_cocos2dx_gui_TextField_getAttachWithIME, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setFontName", js_cocos2dx_gui_TextField_setFontName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getInsertText", js_cocos2dx_gui_TextField_getInsertText, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setInsertText", js_cocos2dx_gui_TextField_setInsertText, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getDetachWithIME", js_cocos2dx_gui_TextField_getDetachWithIME, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("didNotSelectSelf", js_cocos2dx_gui_TextField_didNotSelectSelf, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("attachWithIME", js_cocos2dx_gui_TextField_attachWithIME, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setPasswordEnabled", js_cocos2dx_gui_TextField_setPasswordEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setMaxLengthEnabled", js_cocos2dx_gui_TextField_setMaxLengthEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getDeleteBackward", js_cocos2dx_gui_TextField_getDeleteBackward, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setFontSize", js_cocos2dx_gui_TextField_setFontSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setPlaceHolder", js_cocos2dx_gui_TextField_setPlaceHolder, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isPasswordEnabled", js_cocos2dx_gui_TextField_isPasswordEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getMaxLength", js_cocos2dx_gui_TextField_getMaxLength, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isMaxLengthEnabled", js_cocos2dx_gui_TextField_isMaxLengthEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setDetachWithIME", js_cocos2dx_gui_TextField_setDetachWithIME, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setText", js_cocos2dx_gui_TextField_setText, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setMaxLength", js_cocos2dx_gui_TextField_setMaxLength, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setTouchSize", js_cocos2dx_gui_TextField_setTouchSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setDeleteBackward", js_cocos2dx_gui_TextField_setDeleteBackward, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_gui_TextField_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_gui_TextField_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_gui_Widget_prototype,
		jsb_cocos2d_gui_TextField_class,
		js_cocos2dx_gui_TextField_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "TextField", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::gui::TextField> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_gui_TextField_class;
		p->proto = jsb_cocos2d_gui_TextField_prototype;
		p->parentProto = jsb_cocos2d_gui_Widget_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_gui_TextBMFont_class;
JSObject *jsb_cocos2d_gui_TextBMFont_prototype;

JSBool js_cocos2dx_gui_TextBMFont_setFntFile(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextBMFont* cobj = (cocos2d::gui::TextBMFont *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextBMFont_setFntFile : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_TextBMFont_setFntFile : Error processing arguments");
		cobj->setFntFile(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextBMFont_setFntFile : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextBMFont_getStringValue(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextBMFont* cobj = (cocos2d::gui::TextBMFont *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextBMFont_getStringValue : Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->getStringValue();
		jsval jsret = JSVAL_NULL;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextBMFont_getStringValue : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextBMFont_setText(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::TextBMFont* cobj = (cocos2d::gui::TextBMFont *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_TextBMFont_setText : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_TextBMFont_setText : Error processing arguments");
		cobj->setText(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextBMFont_setText : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_TextBMFont_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::TextBMFont* ret = cocos2d::gui::TextBMFont::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::TextBMFont>(cx, (cocos2d::gui::TextBMFont*)ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "js_cocos2dx_gui_TextBMFont_create : wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_gui_TextBMFont_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::TextBMFont* cobj = new cocos2d::gui::TextBMFont();
		cocos2d::Object *_ccobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::gui::TextBMFont> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::gui::TextBMFont");
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_TextBMFont_constructor : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}


extern JSObject *jsb_cocos2d_gui_Widget_prototype;

void js_cocos2d_gui_TextBMFont_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (TextBMFont)", obj);
}

void js_register_cocos2dx_gui_TextBMFont(JSContext *cx, JSObject *global) {
	jsb_cocos2d_gui_TextBMFont_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_gui_TextBMFont_class->name = "TextBMFont";
	jsb_cocos2d_gui_TextBMFont_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_gui_TextBMFont_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_gui_TextBMFont_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_gui_TextBMFont_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_gui_TextBMFont_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_gui_TextBMFont_class->resolve = JS_ResolveStub;
	jsb_cocos2d_gui_TextBMFont_class->convert = JS_ConvertStub;
	jsb_cocos2d_gui_TextBMFont_class->finalize = js_cocos2d_gui_TextBMFont_finalize;
	jsb_cocos2d_gui_TextBMFont_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("setFntFile", js_cocos2dx_gui_TextBMFont_setFntFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getStringValue", js_cocos2dx_gui_TextBMFont_getStringValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setText", js_cocos2dx_gui_TextBMFont_setText, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_gui_TextBMFont_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_gui_TextBMFont_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_gui_Widget_prototype,
		jsb_cocos2d_gui_TextBMFont_class,
		js_cocos2dx_gui_TextBMFont_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "TextBMFont", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::gui::TextBMFont> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_gui_TextBMFont_class;
		p->proto = jsb_cocos2d_gui_TextBMFont_prototype;
		p->parentProto = jsb_cocos2d_gui_Widget_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_gui_PageView_class;
JSObject *jsb_cocos2d_gui_PageView_prototype;

JSBool js_cocos2dx_gui_PageView_getCurPageIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::PageView* cobj = (cocos2d::gui::PageView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_PageView_getCurPageIndex : Invalid Native Object");
	if (argc == 0) {
		ssize_t ret = cobj->getCurPageIndex();
		jsval jsret = JSVAL_NULL;
		jsret = ssize_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_PageView_getCurPageIndex : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_PageView_addWidgetToPage(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::PageView* cobj = (cocos2d::gui::PageView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_PageView_addWidgetToPage : Invalid Native Object");
	if (argc == 3) {
		cocos2d::gui::Widget* arg0;
		ssize_t arg1;
		JSBool arg2;
		do {
			if (!argv[0].isObject()) { ok = JS_FALSE; break; }
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::gui::Widget*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		ok &= jsval_to_ssize(cx, argv[1], &arg1);
		ok &= JS_ValueToBoolean(cx, argv[2], &arg2);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_PageView_addWidgetToPage : Error processing arguments");
		cobj->addWidgetToPage(arg0, arg1, arg2);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_PageView_addWidgetToPage : wrong number of arguments: %d, was expecting %d", argc, 3);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_PageView_getPage(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::PageView* cobj = (cocos2d::gui::PageView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_PageView_getPage : Invalid Native Object");
	if (argc == 1) {
		ssize_t arg0;
		ok &= jsval_to_ssize(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_PageView_getPage : Error processing arguments");
		cocos2d::gui::Layout* ret = cobj->getPage(arg0);
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::Layout>(cx, (cocos2d::gui::Layout*)ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_PageView_getPage : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_PageView_removePage(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::PageView* cobj = (cocos2d::gui::PageView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_PageView_removePage : Invalid Native Object");
	if (argc == 1) {
		cocos2d::gui::Layout* arg0;
		do {
			if (!argv[0].isObject()) { ok = JS_FALSE; break; }
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::gui::Layout*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_PageView_removePage : Error processing arguments");
		cobj->removePage(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_PageView_removePage : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_PageView_insertPage(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::PageView* cobj = (cocos2d::gui::PageView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_PageView_insertPage : Invalid Native Object");
	if (argc == 2) {
		cocos2d::gui::Layout* arg0;
		int arg1;
		do {
			if (!argv[0].isObject()) { ok = JS_FALSE; break; }
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::gui::Layout*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_PageView_insertPage : Error processing arguments");
		cobj->insertPage(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_PageView_insertPage : wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_PageView_scrollToPage(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::PageView* cobj = (cocos2d::gui::PageView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_PageView_scrollToPage : Invalid Native Object");
	if (argc == 1) {
		ssize_t arg0;
		ok &= jsval_to_ssize(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_PageView_scrollToPage : Error processing arguments");
		cobj->scrollToPage(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_PageView_scrollToPage : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_PageView_removePageAtIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::PageView* cobj = (cocos2d::gui::PageView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_PageView_removePageAtIndex : Invalid Native Object");
	if (argc == 1) {
		ssize_t arg0;
		ok &= jsval_to_ssize(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_PageView_removePageAtIndex : Error processing arguments");
		cobj->removePageAtIndex(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_PageView_removePageAtIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_PageView_getPages(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::PageView* cobj = (cocos2d::gui::PageView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_PageView_getPages : Invalid Native Object");
	if (argc == 0) {
		cocos2d::Vector<cocos2d::gui::Layout *>& ret = cobj->getPages();
		jsval jsret = JSVAL_NULL;
		jsret = ccvector_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_PageView_getPages : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_PageView_removeAllPages(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::PageView* cobj = (cocos2d::gui::PageView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_PageView_removeAllPages : Invalid Native Object");
	if (argc == 0) {
		cobj->removeAllPages();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_PageView_removeAllPages : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_PageView_addPage(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::gui::PageView* cobj = (cocos2d::gui::PageView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_gui_PageView_addPage : Invalid Native Object");
	if (argc == 1) {
		cocos2d::gui::Layout* arg0;
		do {
			if (!argv[0].isObject()) { ok = JS_FALSE; break; }
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::gui::Layout*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_PageView_addPage : Error processing arguments");
		cobj->addPage(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_PageView_addPage : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_gui_PageView_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::PageView* ret = cocos2d::gui::PageView::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::PageView>(cx, (cocos2d::gui::PageView*)ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "js_cocos2dx_gui_PageView_create : wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_gui_PageView_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::gui::PageView* cobj = new cocos2d::gui::PageView();
		cocos2d::Object *_ccobj = dynamic_cast<cocos2d::Object *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::gui::PageView> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::gui::PageView");
		return JS_TRUE;
	}

	JS_ReportError(cx, "js_cocos2dx_gui_PageView_constructor : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}


extern JSObject *jsb_cocos2d_gui_Layout_prototype;

void js_cocos2d_gui_PageView_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PageView)", obj);
}

void js_register_cocos2dx_gui_PageView(JSContext *cx, JSObject *global) {
	jsb_cocos2d_gui_PageView_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_gui_PageView_class->name = "PageView";
	jsb_cocos2d_gui_PageView_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_gui_PageView_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_gui_PageView_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_gui_PageView_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_gui_PageView_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_gui_PageView_class->resolve = JS_ResolveStub;
	jsb_cocos2d_gui_PageView_class->convert = JS_ConvertStub;
	jsb_cocos2d_gui_PageView_class->finalize = js_cocos2d_gui_PageView_finalize;
	jsb_cocos2d_gui_PageView_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getCurPageIndex", js_cocos2dx_gui_PageView_getCurPageIndex, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("addWidgetToPage", js_cocos2dx_gui_PageView_addWidgetToPage, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPage", js_cocos2dx_gui_PageView_getPage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("removePage", js_cocos2dx_gui_PageView_removePage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("insertPage", js_cocos2dx_gui_PageView_insertPage, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("scrollToPage", js_cocos2dx_gui_PageView_scrollToPage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("removePageAtIndex", js_cocos2dx_gui_PageView_removePageAtIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPages", js_cocos2dx_gui_PageView_getPages, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("removeAllPages", js_cocos2dx_gui_PageView_removeAllPages, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("addPage", js_cocos2dx_gui_PageView_addPage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_gui_PageView_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_gui_PageView_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_gui_Layout_prototype,
		jsb_cocos2d_gui_PageView_class,
		js_cocos2dx_gui_PageView_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "PageView", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::gui::PageView> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_gui_PageView_class;
		p->proto = jsb_cocos2d_gui_PageView_prototype;
		p->parentProto = jsb_cocos2d_gui_Layout_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_gui_Helper_class;
JSObject *jsb_cocos2d_gui_Helper_prototype;

JSBool js_cocos2dx_gui_Helper_seekActionWidgetByActionTag(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	if (argc == 2) {
		cocos2d::gui::Widget* arg0;
		int arg1;
		do {
			if (!argv[0].isObject()) { ok = JS_FALSE; break; }
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::gui::Widget*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Helper_seekActionWidgetByActionTag : Error processing arguments");
		cocos2d::gui::Widget* ret = cocos2d::gui::Helper::seekActionWidgetByActionTag(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::Widget>(cx, (cocos2d::gui::Widget*)ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "js_cocos2dx_gui_Helper_seekActionWidgetByActionTag : wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_gui_Helper_seekWidgetByTag(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	if (argc == 2) {
		cocos2d::gui::Widget* arg0;
		int arg1;
		do {
			if (!argv[0].isObject()) { ok = JS_FALSE; break; }
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::gui::Widget*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Helper_seekWidgetByTag : Error processing arguments");
		cocos2d::gui::Widget* ret = cocos2d::gui::Helper::seekWidgetByTag(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::Widget>(cx, (cocos2d::gui::Widget*)ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "js_cocos2dx_gui_Helper_seekWidgetByTag : wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_gui_Helper_seekWidgetByRelativeName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	if (argc == 2) {
		cocos2d::gui::Widget* arg0;
		const char* arg1;
		do {
			if (!argv[0].isObject()) { ok = JS_FALSE; break; }
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::gui::Widget*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Helper_seekWidgetByRelativeName : Error processing arguments");
		cocos2d::gui::Widget* ret = cocos2d::gui::Helper::seekWidgetByRelativeName(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::Widget>(cx, (cocos2d::gui::Widget*)ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "js_cocos2dx_gui_Helper_seekWidgetByRelativeName : wrong number of arguments");
	return JS_FALSE;
}

JSBool js_cocos2dx_gui_Helper_seekWidgetByName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	if (argc == 2) {
		cocos2d::gui::Widget* arg0;
		const char* arg1;
		do {
			if (!argv[0].isObject()) { ok = JS_FALSE; break; }
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::gui::Widget*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_gui_Helper_seekWidgetByName : Error processing arguments");
		cocos2d::gui::Widget* ret = cocos2d::gui::Helper::seekWidgetByName(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::gui::Widget>(cx, (cocos2d::gui::Widget*)ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "js_cocos2dx_gui_Helper_seekWidgetByName : wrong number of arguments");
	return JS_FALSE;
}



void js_cocos2d_gui_Helper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Helper)", obj);
}

void js_register_cocos2dx_gui_Helper(JSContext *cx, JSObject *global) {
	jsb_cocos2d_gui_Helper_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_gui_Helper_class->name = "Helper";
	jsb_cocos2d_gui_Helper_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_gui_Helper_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_gui_Helper_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_gui_Helper_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_gui_Helper_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_gui_Helper_class->resolve = JS_ResolveStub;
	jsb_cocos2d_gui_Helper_class->convert = JS_ConvertStub;
	jsb_cocos2d_gui_Helper_class->finalize = js_cocos2d_gui_Helper_finalize;
	jsb_cocos2d_gui_Helper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	JSPropertySpec *properties = NULL;

	JSFunctionSpec *funcs = NULL;

	static JSFunctionSpec st_funcs[] = {
		JS_FN("seekActionWidgetByActionTag", js_cocos2dx_gui_Helper_seekActionWidgetByActionTag, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("seekWidgetByTag", js_cocos2dx_gui_Helper_seekWidgetByTag, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("seekWidgetByRelativeName", js_cocos2dx_gui_Helper_seekWidgetByRelativeName, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("seekWidgetByName", js_cocos2dx_gui_Helper_seekWidgetByName, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_gui_Helper_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_cocos2d_gui_Helper_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "Helper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::gui::Helper> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_gui_Helper_class;
		p->proto = jsb_cocos2d_gui_Helper_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

void register_all_cocos2dx_gui(JSContext* cx, JSObject* obj) {
	// first, try to get the ns
	JS::RootedValue nsval(cx);
	JSObject *ns;
	JS_GetProperty(cx, obj, "ccui", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, obj, "ccui", nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
	obj = ns;

	js_register_cocos2dx_gui_Widget(cx, obj);
	js_register_cocos2dx_gui_Layout(cx, obj);
	js_register_cocos2dx_gui_PageView(cx, obj);
	js_register_cocos2dx_gui_CheckBox(cx, obj);
	js_register_cocos2dx_gui_Helper(cx, obj);
	js_register_cocos2dx_gui_Text(cx, obj);
	js_register_cocos2dx_gui_Button(cx, obj);
	js_register_cocos2dx_gui_LayoutParameter(cx, obj);
	js_register_cocos2dx_gui_LinearLayoutParameter(cx, obj);
	js_register_cocos2dx_gui_TextBMFont(cx, obj);
	js_register_cocos2dx_gui_ScrollView(cx, obj);
	js_register_cocos2dx_gui_LoadingBar(cx, obj);
	js_register_cocos2dx_gui_Slider(cx, obj);
	js_register_cocos2dx_gui_RelativeLayoutParameter(cx, obj);
	js_register_cocos2dx_gui_ImageView(cx, obj);
	js_register_cocos2dx_gui_TextAtlas(cx, obj);
	js_register_cocos2dx_gui_TextField(cx, obj);
	js_register_cocos2dx_gui_ListView(cx, obj);
}

