#define PY_SSIZE_T_CLEAN
#include <Python.h>

int CallPython() {
    PyObject *pName, *pModule, *pFunc, *pValue;

    Py_SetPythonHome(
        L"C:\\Users\\aslan\\AppData\\Local\\Programs\\Python\\Python312\\");
    Py_SetPath(
        L"C:\\Users\\aslan\\AppData\\Local\\Programs\\Python\\Python312\\Lib;"
        L"C:"
        L"\\Users\\aslan\\AppData\\Local\\Programs\\Python\\Python312\\Lib\\sit"
        L"e-packages;C:"
        L"\\Workspace\\Programming\\Cpp\\ImGui\\OperationBase\\src\\");

    Py_Initialize();

    // Replace "module.py" with the name of your Python script
    pName = PyUnicode_DecodeFSDefault("customreq");

    // Error checking of pName left out for simplicity

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        // Replace "func" with the name of your Python function
        pFunc = PyObject_GetAttrString(pModule, "func");

        if (pFunc && PyCallable_Check(pFunc)) {
            // No arguments in this example
            pValue = PyObject_CallObject(pFunc, NULL);

            if (pValue != NULL) {
                if (PyLong_Check(pValue)) {
                    printf("Result of call: %ld\n", PyLong_AsLong(pValue));
                } else if (PyUnicode_Check(pValue)) {
                    const char *result = PyUnicode_AsUTF8(pValue);
                    printf("Result of call: %s\n", result);
                } else {
                    printf("Result of call: (unsupported data type)\n");
                }
                Py_DECREF(pValue);
            } else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr, "Call failed\n");
                return 1;
            }
        } else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find or call the function\n");
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
        fprintf(stderr, "Failed to load the Python script\n");
        return 1;
    }

    if (Py_FinalizeEx() < 0) {
        return 1;
    }

    return 0;
}
