#include <stdio.h>

/* The template for the virtual function table for printables */
typedef struct printable_vtable {
    void (*print) (void *);
} printable_vtable;

/* Define the printable interface. Note that all interfaces have the same structure:
a void pointer to the underlying concrete type, and a pointer to the concrete type's
implementation of the interface vtable */

typedef struct printable {
    void *val;
    printable_vtable *vt;
} printable;

/* Implement each of the interface's vtable functions as a
polymorphic function for ease of use */

void printable_print(printable p) {
    p.vt->print(p.val);
}

/* Below, we are going to implement a 'printable' interface for 'int' objects */

/* Define how to print ints */

void print_int(void *vi) {
    int *i = vi;
    printf("%d", *i);
}

/* Define a global printable vtable for ints */

printable_vtable int_printable_vtable = {
    .print = print_int
};

/* A function to wrap an int in the printable interface: */

printable int2printable(int *i) {
    return (printable) {
        .val = i,
        .vt = &int_printable_vtable
    };
}

/* Here, we make a similar 'printable' interface for 'double' objects */

/* Define how to print ints */

void print_double(void *vd) {
    double *d = vd;
    printf("%lf", *d);
}

/* Define a global printable vtable for ints */

printable_vtable double_printable_vtable = {
    .print = print_double
};

/* A function to wrap an int in the printable interface: */

printable double2printable(double *d) {
    return (printable) {
        .val = d,
        .vt = &double_printable_vtable
    };
}

/* Now, in main, we'll run printable_print on an int and a double: */

int main() {
    int i=25;
    double d=3708.8;
    printable_print(int2printable(&i));
    puts("");
    /* '25' */
    printable_print(double2printable(&d));
    puts("");
    /* '3708.800000' */
    
    return 0;
}
