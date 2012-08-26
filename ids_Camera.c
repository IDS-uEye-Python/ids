#include <Python.h>
#include "structmember.h"
#include <ueye.h>

#include "ids.h"

static PyObject *ids_Camera_new(PyTypeObject *type, PyObject *args, PyObject *kwds);
static int ids_Camera_init(ids_Camera *self, PyObject *args, PyObject *kwds);

static PyObject *ids_Camera_close(ids_Camera *self, PyObject *args, PyObject *kwds);

PyMemberDef ids_Camera_members[] = {
    {"handle", T_UINT, offsetof(ids_Camera, handle), 0, "camera handle"},
    {NULL}
};

PyTypeObject ids_CameraType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "ids.Camera",              /* tp_name */
    sizeof(ids_Camera),        /* tp_basicsize */
    0,                         /* tp_itemsize */
    0,                         /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,        /* tp_flags */
    "IDS Camera Object",       /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    ids_Camera_methods,        /* tp_methods */
    ids_Camera_members,        /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)ids_Camera_init, /* tp_init */
    0,                         /* tp_alloc */
    ids_Camera_new,            /* tp_new */
};

static PyObject *ids_Camera_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    ids_Camera *self;

    self = (ids_Camera *) type->tp_alloc(type, 0);

    if (self != NULL) {
        self->handle = -1;
    }

    return (PyObject *) self;
}

static int ids_Camera_init(ids_Camera *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = {"handle", NULL};

    /* This means the definition is: def __init__(self, handle=0): */
    self->handle = 0;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|i", kwlist, &self->handle)) {
        return -1;
    }

    /* TODO: Add (more) error checking */
    if (is_InitCamera(&self->handle, NULL) != IS_SUCCESS) {
        PyErr_SetString(PyExc_IOError, "Unable to open camera.");
        return -1;
    }

    return 0;
}
