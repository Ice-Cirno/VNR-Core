
// default includes
#include <shiboken.h>
#include <pysidesignal.h>
#include <pysideproperty.h>
#include <pyside.h>
#include <destroylistener.h>
#include <typeresolver.h>
#include <typeinfo>
#include <signalmanager.h>
#include <pysidemetafunction.h>
#include "pyvnrmem_python.h"

#include "vnrsharedmemory_wrapper.h"

// Extra includes
#include <QList>
#include <qbytearray.h>
#include <qcoreevent.h>
#include <qmetaobject.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qthread.h>
#include <vnrsharedmemory.h>


// Native ---------------------------------------------------------

void VnrSharedMemoryWrapper::pysideInitQtMetaTypes()
{
}

VnrSharedMemoryWrapper::VnrSharedMemoryWrapper(QObject * parent) : VnrSharedMemory(parent) {
    // ... middle
}

VnrSharedMemoryWrapper::VnrSharedMemoryWrapper(const QString & key, QObject * parent) : VnrSharedMemory(key, parent) {
    // ... middle
}

void VnrSharedMemoryWrapper::childEvent(QChildEvent * arg__1)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return ;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "childEvent"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QObject::childEvent(arg__1);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython((SbkObjectType*)SbkPySide_QtCoreTypes[SBK_QCHILDEVENT_IDX], arg__1)
    ));
    bool invalidateArg1 = PyTuple_GET_ITEM(pyArgs, 0)->ob_refcnt == 1;

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return ;
    }
    if (invalidateArg1)
        Shiboken::Object::invalidate(PyTuple_GET_ITEM(pyArgs, 0));
}

void VnrSharedMemoryWrapper::connectNotify(const char * signal)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return ;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "connectNotify"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QObject::connectNotify(signal);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<const char*>(), signal)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return ;
    }
}

void VnrSharedMemoryWrapper::customEvent(QEvent * arg__1)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return ;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "customEvent"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QObject::customEvent(arg__1);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython((SbkObjectType*)SbkPySide_QtCoreTypes[SBK_QEVENT_IDX], arg__1)
    ));
    bool invalidateArg1 = PyTuple_GET_ITEM(pyArgs, 0)->ob_refcnt == 1;

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return ;
    }
    if (invalidateArg1)
        Shiboken::Object::invalidate(PyTuple_GET_ITEM(pyArgs, 0));
}

void VnrSharedMemoryWrapper::disconnectNotify(const char * signal)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return ;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "disconnectNotify"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QObject::disconnectNotify(signal);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<const char*>(), signal)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return ;
    }
}

bool VnrSharedMemoryWrapper::event(QEvent * arg__1)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return ((bool)0);
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "event"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QObject::event(arg__1);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython((SbkObjectType*)SbkPySide_QtCoreTypes[SBK_QEVENT_IDX], arg__1)
    ));
    bool invalidateArg1 = PyTuple_GET_ITEM(pyArgs, 0)->ob_refcnt == 1;

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return ((bool)0);
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "VnrSharedMemory.event", "bool", pyResult->ob_type->tp_name);
        return ((bool)0);
    }
    bool cppResult;
    pythonToCpp(pyResult, &cppResult);
    if (invalidateArg1)
        Shiboken::Object::invalidate(PyTuple_GET_ITEM(pyArgs, 0));
    return cppResult;
}

bool VnrSharedMemoryWrapper::eventFilter(QObject * arg__1, QEvent * arg__2)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return ((bool)0);
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "eventFilter"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QObject::eventFilter(arg__1, arg__2);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(NN)",
        Shiboken::Conversions::pointerToPython((SbkObjectType*)SbkPySide_QtCoreTypes[SBK_QOBJECT_IDX], arg__1),
        Shiboken::Conversions::pointerToPython((SbkObjectType*)SbkPySide_QtCoreTypes[SBK_QEVENT_IDX], arg__2)
    ));
    bool invalidateArg2 = PyTuple_GET_ITEM(pyArgs, 1)->ob_refcnt == 1;

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return ((bool)0);
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "VnrSharedMemory.eventFilter", "bool", pyResult->ob_type->tp_name);
        return ((bool)0);
    }
    bool cppResult;
    pythonToCpp(pyResult, &cppResult);
    if (invalidateArg2)
        Shiboken::Object::invalidate(PyTuple_GET_ITEM(pyArgs, 1));
    return cppResult;
}

void VnrSharedMemoryWrapper::timerEvent(QTimerEvent * arg__1)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return ;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "timerEvent"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QObject::timerEvent(arg__1);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython((SbkObjectType*)SbkPySide_QtCoreTypes[SBK_QTIMEREVENT_IDX], arg__1)
    ));
    bool invalidateArg1 = PyTuple_GET_ITEM(pyArgs, 0)->ob_refcnt == 1;

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return ;
    }
    if (invalidateArg1)
        Shiboken::Object::invalidate(PyTuple_GET_ITEM(pyArgs, 0));
}

const QMetaObject* VnrSharedMemoryWrapper::metaObject() const
{
    #if QT_VERSION >= 0x040700
    if (QObject::d_ptr->metaObject) return QObject::d_ptr->metaObject;
    #endif
    SbkObject* pySelf = Shiboken::BindingManager::instance().retrieveWrapper(this);
    if (pySelf == NULL)
        return VnrSharedMemory::metaObject();
    return PySide::SignalManager::retriveMetaObject(reinterpret_cast<PyObject*>(pySelf));
}

int VnrSharedMemoryWrapper::qt_metacall(QMetaObject::Call call, int id, void** args)
{
    int result = VnrSharedMemory::qt_metacall(call, id, args);
    return result < 0 ? result : PySide::SignalManager::qt_metacall(this, call, id, args);
}

void* VnrSharedMemoryWrapper::qt_metacast(const char* _clname)
{
        if (!_clname) return 0;
        SbkObject* pySelf = Shiboken::BindingManager::instance().retrieveWrapper(this);
        if (pySelf && PySide::inherits(Py_TYPE(pySelf), _clname))
                return static_cast<void*>(const_cast< VnrSharedMemoryWrapper* >(this));
        return VnrSharedMemory::qt_metacast(_clname);
}

VnrSharedMemoryWrapper::~VnrSharedMemoryWrapper()
{
    SbkObject* wrapper = Shiboken::BindingManager::instance().retrieveWrapper(this);
    Shiboken::Object::destroy(wrapper, this);
}

// Target ---------------------------------------------------------

extern "C" {
static int
Sbk_VnrSharedMemory_Init(PyObject* self, PyObject* args, PyObject* kwds)
{
    const char* argNames[] = {"parent"};
    const QMetaObject* metaObject;
    SbkObject* sbkSelf = reinterpret_cast<SbkObject*>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::VnrSharedMemory >()))
        return -1;

    ::VnrSharedMemoryWrapper* cptr = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_ParseTuple(args, "|OO:VnrSharedMemory", &(pyArgs[0]), &(pyArgs[1])))
        return -1;


    // Overloaded function decisor
    // 0: VnrSharedMemory(QObject*)
    // 1: VnrSharedMemory(QString,QObject*)
    if (numArgs == 0) {
        overloadId = 0; // VnrSharedMemory(QObject*)
    } else if ((pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible((SbkObjectType*)SbkPySide_QtCoreTypes[SBK_QOBJECT_IDX], (pyArgs[0])))) {
        overloadId = 0; // VnrSharedMemory(QObject*)
    } else if ((pythonToCpp[0] = Shiboken::Conversions::isPythonToCppConvertible(SbkPySide_QtCoreTypeConverters[SBK_QSTRING_IDX], (pyArgs[0])))) {
        if (numArgs == 1) {
            overloadId = 1; // VnrSharedMemory(QString,QObject*)
        } else if ((pythonToCpp[1] = Shiboken::Conversions::isPythonToCppPointerConvertible((SbkObjectType*)SbkPySide_QtCoreTypes[SBK_QOBJECT_IDX], (pyArgs[1])))) {
            overloadId = 1; // VnrSharedMemory(QString,QObject*)
        }
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_VnrSharedMemory_Init_TypeError;

    // Call function/method
    switch (overloadId) {
        case 0: // VnrSharedMemory(QObject * parent)
        {
            if (kwds) {
                PyObject* value = PyDict_GetItemString(kwds, "parent");
                if (value && pyArgs[0]) {
                    PyErr_SetString(PyExc_TypeError, "pyvnrmem.VnrSharedMemory(): got multiple values for keyword argument 'parent'.");
                    return -1;
                } else if (value) {
                    pyArgs[0] = value;
                    if (!(pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible((SbkObjectType*)SbkPySide_QtCoreTypes[SBK_QOBJECT_IDX], (pyArgs[0]))))
                        goto Sbk_VnrSharedMemory_Init_TypeError;
                }
            }
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::QObject* cppArg0 = nullptr;
            if (pythonToCpp[0]) pythonToCpp[0](pyArgs[0], &cppArg0);

            if (!PyErr_Occurred()) {
                // VnrSharedMemory(QObject*)
                void* addr = PySide::nextQObjectMemoryAddr();
                PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
                if (addr) {
                    cptr = new (addr) ::VnrSharedMemoryWrapper(cppArg0);
                    PySide::setNextQObjectMemoryAddr(0);
                } else {
                    cptr = new ::VnrSharedMemoryWrapper(cppArg0);
                }

                PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
                Shiboken::Object::setParent(pyArgs[0], self);
            }
            break;
        }
        case 1: // VnrSharedMemory(const QString & key, QObject * parent)
        {
            if (kwds) {
                PyObject* value = PyDict_GetItemString(kwds, "parent");
                if (value && pyArgs[1]) {
                    PyErr_SetString(PyExc_TypeError, "pyvnrmem.VnrSharedMemory(): got multiple values for keyword argument 'parent'.");
                    return -1;
                } else if (value) {
                    pyArgs[1] = value;
                    if (!(pythonToCpp[1] = Shiboken::Conversions::isPythonToCppPointerConvertible((SbkObjectType*)SbkPySide_QtCoreTypes[SBK_QOBJECT_IDX], (pyArgs[1]))))
                        goto Sbk_VnrSharedMemory_Init_TypeError;
                }
            }
            ::QString cppArg0 = ::QString();
            pythonToCpp[0](pyArgs[0], &cppArg0);
            if (!Shiboken::Object::isValid(pyArgs[1]))
                return -1;
            ::QObject* cppArg1 = nullptr;
            if (pythonToCpp[1]) pythonToCpp[1](pyArgs[1], &cppArg1);

            if (!PyErr_Occurred()) {
                // VnrSharedMemory(QString,QObject*)
                void* addr = PySide::nextQObjectMemoryAddr();
                PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
                if (addr) {
                    cptr = new (addr) ::VnrSharedMemoryWrapper(cppArg0, cppArg1);
                    PySide::setNextQObjectMemoryAddr(0);
                } else {
                    cptr = new ::VnrSharedMemoryWrapper(cppArg0, cppArg1);
                }

                PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
                Shiboken::Object::setParent(pyArgs[1], self);
            }
            break;
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::VnrSharedMemory >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_VnrSharedMemory_Init_TypeError;

    Shiboken::Object::setValidCpp(sbkSelf, true);
    Shiboken::Object::setHasCppWrapper(sbkSelf, true);
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);

    // QObject setup
    PySide::Signal::updateSourceObject(self);
    metaObject = cptr->metaObject(); // <- init python qt properties
    if (kwds && !PySide::fillQtProperties(self, metaObject, kwds, argNames, 1))
        return -1;


    return 1;

    Sbk_VnrSharedMemory_Init_TypeError:
        const char* overloads[] = {"PySide.QtCore.QObject = nullptr", "unicode, PySide.QtCore.QObject = nullptr", 0};
        Shiboken::setErrorAboutWrongArguments(args, "pyvnrmem.VnrSharedMemory", overloads);
        return -1;
}

static PyObject* Sbk_VnrSharedMemoryFunc_attach(PyObject* self, PyObject* args, PyObject* kwds)
{
    VnrSharedMemoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (VnrSharedMemoryWrapper*)((::VnrSharedMemory*)Shiboken::Conversions::cppPointer(SbkpyvnrmemTypes[SBK_VNRSHAREDMEMORY_IDX], (SbkObject*)self));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0 };
    SBK_UNUSED(pythonToCpp)
    int numNamedArgs = (kwds ? PyDict_Size(kwds) : 0);
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0};

    // invalid argument lengths
    if (numArgs + numNamedArgs > 1) {
        PyErr_SetString(PyExc_TypeError, "pyvnrmem.VnrSharedMemory.attach(): too many arguments");
        return 0;
    }

    if (!PyArg_ParseTuple(args, "|O:attach", &(pyArgs[0])))
        return 0;


    // Overloaded function decisor
    // 0: attach(bool)
    if (numArgs == 0) {
        overloadId = 0; // attach(bool)
    } else if ((pythonToCpp[0] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), (pyArgs[0])))) {
        overloadId = 0; // attach(bool)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_VnrSharedMemoryFunc_attach_TypeError;

    // Call function/method
    {
        if (kwds) {
            PyObject* value = PyDict_GetItemString(kwds, "readOnly");
            if (value && pyArgs[0]) {
                PyErr_SetString(PyExc_TypeError, "pyvnrmem.VnrSharedMemory.attach(): got multiple values for keyword argument 'readOnly'.");
                return 0;
            } else if (value) {
                pyArgs[0] = value;
                if (!(pythonToCpp[0] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), (pyArgs[0]))))
                    goto Sbk_VnrSharedMemoryFunc_attach_TypeError;
            }
        }
        bool cppArg0 = false;
        if (pythonToCpp[0]) pythonToCpp[0](pyArgs[0], &cppArg0);

        if (!PyErr_Occurred()) {
            // attach(bool)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            bool cppResult = cppSelf->attach(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_VnrSharedMemoryFunc_attach_TypeError:
        const char* overloads[] = {"bool = false", 0};
        Shiboken::setErrorAboutWrongArguments(args, "pyvnrmem.VnrSharedMemory.attach", overloads);
        return 0;
}

static PyObject* Sbk_VnrSharedMemoryFunc_constData(PyObject* self)
{
    VnrSharedMemoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (VnrSharedMemoryWrapper*)((::VnrSharedMemory*)Shiboken::Conversions::cppPointer(SbkpyvnrmemTypes[SBK_VNRSHAREDMEMORY_IDX], (SbkObject*)self));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // constData()const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            const char * cppResult = const_cast<const ::VnrSharedMemoryWrapper*>(cppSelf)->constData();
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<const char*>(), cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_VnrSharedMemoryFunc_create(PyObject* self, PyObject* args, PyObject* kwds)
{
    VnrSharedMemoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (VnrSharedMemoryWrapper*)((::VnrSharedMemory*)Shiboken::Conversions::cppPointer(SbkpyvnrmemTypes[SBK_VNRSHAREDMEMORY_IDX], (SbkObject*)self));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numNamedArgs = (kwds ? PyDict_Size(kwds) : 0);
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths
    if (numArgs + numNamedArgs > 2) {
        PyErr_SetString(PyExc_TypeError, "pyvnrmem.VnrSharedMemory.create(): too many arguments");
        return 0;
    } else if (numArgs < 1) {
        PyErr_SetString(PyExc_TypeError, "pyvnrmem.VnrSharedMemory.create(): not enough arguments");
        return 0;
    }

    if (!PyArg_ParseTuple(args, "|OO:create", &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: create(int,bool)
    if ((pythonToCpp[0] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<int>(), (pyArgs[0])))) {
        if (numArgs == 1) {
            overloadId = 0; // create(int,bool)
        } else if ((pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), (pyArgs[1])))) {
            overloadId = 0; // create(int,bool)
        }
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_VnrSharedMemoryFunc_create_TypeError;

    // Call function/method
    {
        if (kwds) {
            PyObject* value = PyDict_GetItemString(kwds, "readOnly");
            if (value && pyArgs[1]) {
                PyErr_SetString(PyExc_TypeError, "pyvnrmem.VnrSharedMemory.create(): got multiple values for keyword argument 'readOnly'.");
                return 0;
            } else if (value) {
                pyArgs[1] = value;
                if (!(pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), (pyArgs[1]))))
                    goto Sbk_VnrSharedMemoryFunc_create_TypeError;
            }
        }
        int cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        bool cppArg1 = false;
        if (pythonToCpp[1]) pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // create(int,bool)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            bool cppResult = cppSelf->create(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_VnrSharedMemoryFunc_create_TypeError:
        const char* overloads[] = {"int, bool = false", 0};
        Shiboken::setErrorAboutWrongArguments(args, "pyvnrmem.VnrSharedMemory.create", overloads);
        return 0;
}

static PyObject* Sbk_VnrSharedMemoryFunc_dataHash(PyObject* self)
{
    VnrSharedMemoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (VnrSharedMemoryWrapper*)((::VnrSharedMemory*)Shiboken::Conversions::cppPointer(SbkpyvnrmemTypes[SBK_VNRSHAREDMEMORY_IDX], (SbkObject*)self));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // dataHash()const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            qint64 cppResult = const_cast<const ::VnrSharedMemoryWrapper*>(cppSelf)->dataHash();
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<qint64>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_VnrSharedMemoryFunc_dataRole(PyObject* self)
{
    VnrSharedMemoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (VnrSharedMemoryWrapper*)((::VnrSharedMemory*)Shiboken::Conversions::cppPointer(SbkpyvnrmemTypes[SBK_VNRSHAREDMEMORY_IDX], (SbkObject*)self));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // dataRole()const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            qint8 cppResult = const_cast<const ::VnrSharedMemoryWrapper*>(cppSelf)->dataRole();
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<qint8>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_VnrSharedMemoryFunc_dataStatus(PyObject* self)
{
    VnrSharedMemoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (VnrSharedMemoryWrapper*)((::VnrSharedMemory*)Shiboken::Conversions::cppPointer(SbkpyvnrmemTypes[SBK_VNRSHAREDMEMORY_IDX], (SbkObject*)self));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // dataStatus()const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            qint8 cppResult = const_cast<const ::VnrSharedMemoryWrapper*>(cppSelf)->dataStatus();
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<qint8>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_VnrSharedMemoryFunc_dataText(PyObject* self)
{
    VnrSharedMemoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (VnrSharedMemoryWrapper*)((::VnrSharedMemory*)Shiboken::Conversions::cppPointer(SbkpyvnrmemTypes[SBK_VNRSHAREDMEMORY_IDX], (SbkObject*)self));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // dataText()const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QString cppResult = const_cast<const ::VnrSharedMemoryWrapper*>(cppSelf)->dataText();
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_VnrSharedMemoryFunc_dataTextMaximumSize(PyObject* self)
{
    VnrSharedMemoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (VnrSharedMemoryWrapper*)((::VnrSharedMemory*)Shiboken::Conversions::cppPointer(SbkpyvnrmemTypes[SBK_VNRSHAREDMEMORY_IDX], (SbkObject*)self));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // dataTextMaximumSize()const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            int cppResult = const_cast<const ::VnrSharedMemoryWrapper*>(cppSelf)->dataTextMaximumSize();
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<int>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_VnrSharedMemoryFunc_errorString(PyObject* self)
{
    VnrSharedMemoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (VnrSharedMemoryWrapper*)((::VnrSharedMemory*)Shiboken::Conversions::cppPointer(SbkpyvnrmemTypes[SBK_VNRSHAREDMEMORY_IDX], (SbkObject*)self));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // errorString()const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QString cppResult = const_cast<const ::VnrSharedMemoryWrapper*>(cppSelf)->errorString();
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_VnrSharedMemoryFunc_hasError(PyObject* self)
{
    VnrSharedMemoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (VnrSharedMemoryWrapper*)((::VnrSharedMemory*)Shiboken::Conversions::cppPointer(SbkpyvnrmemTypes[SBK_VNRSHAREDMEMORY_IDX], (SbkObject*)self));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // hasError()const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            bool cppResult = const_cast<const ::VnrSharedMemoryWrapper*>(cppSelf)->hasError();
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_VnrSharedMemoryFunc_isAttached(PyObject* self)
{
    VnrSharedMemoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (VnrSharedMemoryWrapper*)((::VnrSharedMemory*)Shiboken::Conversions::cppPointer(SbkpyvnrmemTypes[SBK_VNRSHAREDMEMORY_IDX], (SbkObject*)self));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // isAttached()const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            bool cppResult = const_cast<const ::VnrSharedMemoryWrapper*>(cppSelf)->isAttached();
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_VnrSharedMemoryFunc_key(PyObject* self)
{
    VnrSharedMemoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (VnrSharedMemoryWrapper*)((::VnrSharedMemory*)Shiboken::Conversions::cppPointer(SbkpyvnrmemTypes[SBK_VNRSHAREDMEMORY_IDX], (SbkObject*)self));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // key()const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QString cppResult = const_cast<const ::VnrSharedMemoryWrapper*>(cppSelf)->key();
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_VnrSharedMemoryFunc_lock(PyObject* self)
{
    VnrSharedMemoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (VnrSharedMemoryWrapper*)((::VnrSharedMemory*)Shiboken::Conversions::cppPointer(SbkpyvnrmemTypes[SBK_VNRSHAREDMEMORY_IDX], (SbkObject*)self));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // lock()
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            bool cppResult = cppSelf->lock();
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_VnrSharedMemoryFunc_setDataHash(PyObject* self, PyObject* pyArg)
{
    VnrSharedMemoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (VnrSharedMemoryWrapper*)((::VnrSharedMemory*)Shiboken::Conversions::cppPointer(SbkpyvnrmemTypes[SBK_VNRSHAREDMEMORY_IDX], (SbkObject*)self));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: setDataHash(qint64)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<qint64>(), (pyArg)))) {
        overloadId = 0; // setDataHash(qint64)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_VnrSharedMemoryFunc_setDataHash_TypeError;

    // Call function/method
    {
        qint64 cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // setDataHash(qint64)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setDataHash(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_VnrSharedMemoryFunc_setDataHash_TypeError:
        const char* overloads[] = {"long long", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "pyvnrmem.VnrSharedMemory.setDataHash", overloads);
        return 0;
}

static PyObject* Sbk_VnrSharedMemoryFunc_setDataRole(PyObject* self, PyObject* pyArg)
{
    VnrSharedMemoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (VnrSharedMemoryWrapper*)((::VnrSharedMemory*)Shiboken::Conversions::cppPointer(SbkpyvnrmemTypes[SBK_VNRSHAREDMEMORY_IDX], (SbkObject*)self));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: setDataRole(qint8)
    if (SbkChar_Check(pyArg) && (pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<qint8>(), (pyArg)))) {
        overloadId = 0; // setDataRole(qint8)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_VnrSharedMemoryFunc_setDataRole_TypeError;

    // Call function/method
    {
        qint8 cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // setDataRole(qint8)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setDataRole(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_VnrSharedMemoryFunc_setDataRole_TypeError:
        const char* overloads[] = {"char", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "pyvnrmem.VnrSharedMemory.setDataRole", overloads);
        return 0;
}

static PyObject* Sbk_VnrSharedMemoryFunc_setDataStatus(PyObject* self, PyObject* pyArg)
{
    VnrSharedMemoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (VnrSharedMemoryWrapper*)((::VnrSharedMemory*)Shiboken::Conversions::cppPointer(SbkpyvnrmemTypes[SBK_VNRSHAREDMEMORY_IDX], (SbkObject*)self));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: setDataStatus(qint8)
    if (SbkChar_Check(pyArg) && (pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<qint8>(), (pyArg)))) {
        overloadId = 0; // setDataStatus(qint8)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_VnrSharedMemoryFunc_setDataStatus_TypeError;

    // Call function/method
    {
        qint8 cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // setDataStatus(qint8)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setDataStatus(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_VnrSharedMemoryFunc_setDataStatus_TypeError:
        const char* overloads[] = {"char", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "pyvnrmem.VnrSharedMemory.setDataStatus", overloads);
        return 0;
}

static PyObject* Sbk_VnrSharedMemoryFunc_setDataText(PyObject* self, PyObject* pyArg)
{
    VnrSharedMemoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (VnrSharedMemoryWrapper*)((::VnrSharedMemory*)Shiboken::Conversions::cppPointer(SbkpyvnrmemTypes[SBK_VNRSHAREDMEMORY_IDX], (SbkObject*)self));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: setDataText(QString)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(SbkPySide_QtCoreTypeConverters[SBK_QSTRING_IDX], (pyArg)))) {
        overloadId = 0; // setDataText(QString)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_VnrSharedMemoryFunc_setDataText_TypeError;

    // Call function/method
    {
        ::QString cppArg0 = ::QString();
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // setDataText(QString)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setDataText(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_VnrSharedMemoryFunc_setDataText_TypeError:
        const char* overloads[] = {"unicode", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "pyvnrmem.VnrSharedMemory.setDataText", overloads);
        return 0;
}

static PyObject* Sbk_VnrSharedMemoryFunc_setKey(PyObject* self, PyObject* pyArg)
{
    VnrSharedMemoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (VnrSharedMemoryWrapper*)((::VnrSharedMemory*)Shiboken::Conversions::cppPointer(SbkpyvnrmemTypes[SBK_VNRSHAREDMEMORY_IDX], (SbkObject*)self));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: setKey(QString)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(SbkPySide_QtCoreTypeConverters[SBK_QSTRING_IDX], (pyArg)))) {
        overloadId = 0; // setKey(QString)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_VnrSharedMemoryFunc_setKey_TypeError;

    // Call function/method
    {
        ::QString cppArg0 = ::QString();
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // setKey(QString)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setKey(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_VnrSharedMemoryFunc_setKey_TypeError:
        const char* overloads[] = {"unicode", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "pyvnrmem.VnrSharedMemory.setKey", overloads);
        return 0;
}

static PyObject* Sbk_VnrSharedMemoryFunc_size(PyObject* self)
{
    VnrSharedMemoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (VnrSharedMemoryWrapper*)((::VnrSharedMemory*)Shiboken::Conversions::cppPointer(SbkpyvnrmemTypes[SBK_VNRSHAREDMEMORY_IDX], (SbkObject*)self));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // size()const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            int cppResult = const_cast<const ::VnrSharedMemoryWrapper*>(cppSelf)->size();
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<int>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_VnrSharedMemoryFunc_unlock(PyObject* self)
{
    VnrSharedMemoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (VnrSharedMemoryWrapper*)((::VnrSharedMemory*)Shiboken::Conversions::cppPointer(SbkpyvnrmemTypes[SBK_VNRSHAREDMEMORY_IDX], (SbkObject*)self));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // unlock()
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            bool cppResult = cppSelf->unlock();
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyMethodDef Sbk_VnrSharedMemory_methods[] = {
    {"attach", (PyCFunction)Sbk_VnrSharedMemoryFunc_attach, METH_VARARGS|METH_KEYWORDS},
    {"constData", (PyCFunction)Sbk_VnrSharedMemoryFunc_constData, METH_NOARGS},
    {"create", (PyCFunction)Sbk_VnrSharedMemoryFunc_create, METH_VARARGS|METH_KEYWORDS},
    {"dataHash", (PyCFunction)Sbk_VnrSharedMemoryFunc_dataHash, METH_NOARGS},
    {"dataRole", (PyCFunction)Sbk_VnrSharedMemoryFunc_dataRole, METH_NOARGS},
    {"dataStatus", (PyCFunction)Sbk_VnrSharedMemoryFunc_dataStatus, METH_NOARGS},
    {"dataText", (PyCFunction)Sbk_VnrSharedMemoryFunc_dataText, METH_NOARGS},
    {"dataTextMaximumSize", (PyCFunction)Sbk_VnrSharedMemoryFunc_dataTextMaximumSize, METH_NOARGS},
    {"errorString", (PyCFunction)Sbk_VnrSharedMemoryFunc_errorString, METH_NOARGS},
    {"hasError", (PyCFunction)Sbk_VnrSharedMemoryFunc_hasError, METH_NOARGS},
    {"isAttached", (PyCFunction)Sbk_VnrSharedMemoryFunc_isAttached, METH_NOARGS},
    {"key", (PyCFunction)Sbk_VnrSharedMemoryFunc_key, METH_NOARGS},
    {"lock", (PyCFunction)Sbk_VnrSharedMemoryFunc_lock, METH_NOARGS},
    {"setDataHash", (PyCFunction)Sbk_VnrSharedMemoryFunc_setDataHash, METH_O},
    {"setDataRole", (PyCFunction)Sbk_VnrSharedMemoryFunc_setDataRole, METH_O},
    {"setDataStatus", (PyCFunction)Sbk_VnrSharedMemoryFunc_setDataStatus, METH_O},
    {"setDataText", (PyCFunction)Sbk_VnrSharedMemoryFunc_setDataText, METH_O},
    {"setKey", (PyCFunction)Sbk_VnrSharedMemoryFunc_setKey, METH_O},
    {"size", (PyCFunction)Sbk_VnrSharedMemoryFunc_size, METH_NOARGS},
    {"unlock", (PyCFunction)Sbk_VnrSharedMemoryFunc_unlock, METH_NOARGS},

    {0} // Sentinel
};

} // extern "C"

static int Sbk_VnrSharedMemory_traverse(PyObject* self, visitproc visit, void* arg)
{
    return reinterpret_cast<PyTypeObject*>(&SbkObject_Type)->tp_traverse(self, visit, arg);
}
static int Sbk_VnrSharedMemory_clear(PyObject* self)
{
    return reinterpret_cast<PyTypeObject*>(&SbkObject_Type)->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType Sbk_VnrSharedMemory_Type = { { {
    PyVarObject_HEAD_INIT(&SbkObjectType_Type, 0)
    /*tp_name*/             "pyvnrmem.VnrSharedMemory",
    /*tp_basicsize*/        sizeof(SbkObject),
    /*tp_itemsize*/         0,
    /*tp_dealloc*/          &SbkDeallocWrapper,
    /*tp_print*/            0,
    /*tp_getattr*/          0,
    /*tp_setattr*/          0,
    /*tp_compare*/          0,
    /*tp_repr*/             0,
    /*tp_as_number*/        0,
    /*tp_as_sequence*/      0,
    /*tp_as_mapping*/       0,
    /*tp_hash*/             0,
    /*tp_call*/             0,
    /*tp_str*/              0,
    /*tp_getattro*/         0,
    /*tp_setattro*/         0,
    /*tp_as_buffer*/        0,
    /*tp_flags*/            Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    /*tp_doc*/              0,
    /*tp_traverse*/         Sbk_VnrSharedMemory_traverse,
    /*tp_clear*/            Sbk_VnrSharedMemory_clear,
    /*tp_richcompare*/      0,
    /*tp_weaklistoffset*/   0,
    /*tp_iter*/             0,
    /*tp_iternext*/         0,
    /*tp_methods*/          Sbk_VnrSharedMemory_methods,
    /*tp_members*/          0,
    /*tp_getset*/           0,
    /*tp_base*/             0,
    /*tp_dict*/             0,
    /*tp_descr_get*/        0,
    /*tp_descr_set*/        0,
    /*tp_dictoffset*/       0,
    /*tp_init*/             Sbk_VnrSharedMemory_Init,
    /*tp_alloc*/            0,
    /*tp_new*/              SbkObjectTpNew,
    /*tp_free*/             0,
    /*tp_is_gc*/            0,
    /*tp_bases*/            0,
    /*tp_mro*/              0,
    /*tp_cache*/            0,
    /*tp_subclasses*/       0,
    /*tp_weaklist*/         0
}, },
    /*priv_data*/           0
};
} //extern

static void* Sbk_VnrSharedMemory_typeDiscovery(void* cptr, SbkObjectType* instanceType)
{
    if (instanceType == reinterpret_cast<SbkObjectType*>(Shiboken::SbkType< ::QObject >()))
        return dynamic_cast< ::VnrSharedMemory*>(reinterpret_cast< ::QObject*>(cptr));
    return 0;
}


// Type conversion functions.

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void VnrSharedMemory_PythonToCpp_VnrSharedMemory_PTR(PyObject* pyIn, void* cppOut) {
    Shiboken::Conversions::pythonToCppPointer(&Sbk_VnrSharedMemory_Type, pyIn, cppOut);
}
static PythonToCppFunc is_VnrSharedMemory_PythonToCpp_VnrSharedMemory_PTR_Convertible(PyObject* pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, (PyTypeObject*)&Sbk_VnrSharedMemory_Type))
        return VnrSharedMemory_PythonToCpp_VnrSharedMemory_PTR;
    return 0;
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject* VnrSharedMemory_PTR_CppToPython_VnrSharedMemory(const void* cppIn) {
    return PySide::getWrapperForQObject((::VnrSharedMemory*)cppIn, &Sbk_VnrSharedMemory_Type);

}

void init_VnrSharedMemory(PyObject* module)
{
    SbkpyvnrmemTypes[SBK_VNRSHAREDMEMORY_IDX] = reinterpret_cast<PyTypeObject*>(&Sbk_VnrSharedMemory_Type);

    if (!Shiboken::ObjectType::introduceWrapperType(module, "VnrSharedMemory", "VnrSharedMemory*",
        &Sbk_VnrSharedMemory_Type, &Shiboken::callCppDestructor< ::VnrSharedMemory >, (SbkObjectType*)SbkPySide_QtCoreTypes[SBK_QOBJECT_IDX])) {
        return;
    }

    // Register Converter
    SbkConverter* converter = Shiboken::Conversions::createConverter(&Sbk_VnrSharedMemory_Type,
        VnrSharedMemory_PythonToCpp_VnrSharedMemory_PTR,
        is_VnrSharedMemory_PythonToCpp_VnrSharedMemory_PTR_Convertible,
        VnrSharedMemory_PTR_CppToPython_VnrSharedMemory);

    Shiboken::Conversions::registerConverterName(converter, "VnrSharedMemory");
    Shiboken::Conversions::registerConverterName(converter, "VnrSharedMemory*");
    Shiboken::Conversions::registerConverterName(converter, "VnrSharedMemory&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::VnrSharedMemory).name());
    Shiboken::Conversions::registerConverterName(converter, typeid(::VnrSharedMemoryWrapper).name());


    Shiboken::ObjectType::setTypeDiscoveryFunctionV2(&Sbk_VnrSharedMemory_Type, &Sbk_VnrSharedMemory_typeDiscovery);

    PySide::Signal::registerSignals(&Sbk_VnrSharedMemory_Type, &::VnrSharedMemory::staticMetaObject);

    VnrSharedMemoryWrapper::pysideInitQtMetaTypes();
    Shiboken::ObjectType::setSubTypeInitHook(&Sbk_VnrSharedMemory_Type, &PySide::initQObjectSubType);
    PySide::initDynamicMetaObject(&Sbk_VnrSharedMemory_Type, &::VnrSharedMemory::staticMetaObject, sizeof(::VnrSharedMemory));
}
