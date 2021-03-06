#ifndef ADVMATH_C
#define ADVMATH_C

#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
    float f_value;
    struct _Node *next;
} _Node;

typedef struct _DNode
{
    float f_value;
    struct _DNode *next;
    struct _DNode *prev;
};

typedef struct Vector
{
    struct _Node *first;
    struct _Node *last;
    unsigned char size;
} Vector;

typedef struct SortedVector
{
    struct _DNode *first;
    struct _DNode *last;
    unsigned char size;
} SortedVector;

typedef struct Vector3
{
    float x;
    float y;
    float z;
} Vector3;

typedef struct Point
{
    float x;
    float y;
    float z;
} Point;

/* Creates and assignes a new VectorArray struct and returns it*/
Vector *newVector(float value);

/* Creates and adds a new Node to the beginning of a vector*/
Vector *V_addFirst(Vector *v, float value);

/* Creates and adds a new Node to the vector*/
Vector *V_add(Vector *v, float value, int index);

/* Creates and adds a new Node to the end of a vector*/
Vector *V_addLast(Vector *v, float value);

/* Returnes the value of a specific index*/
float V_get(Vector *v, int index);

/* Removes the Node of a specific index*/
Vector *V_remove(Vector *v, int index);

/* Creates and assignes a new VectorArray struct and returns it*/
SortedVector *newSortedVector(float value);

/* Creates and adds a new Node to the SortedVector*/
SortedVector *SV_add(SortedVector *v, float value);

/* Returnes the value of a specific index*/
float SV_get(SortedVector *v, int index);

/* Removes the Node of a specific index*/
SortedVector *SV_remove(SortedVector *v, int index);

/* Creates and assignes a new Vector3 struct and returns it*/
Vector3 *newVector3(float x, float y, float z);

/* assignes values to a Vector3 struct and returns it*/
Vector3 *V3_assign(Vector3 *v, float x, float y, float z);

/* dots the 2 Vector3s and returns the result */
float V3_dotProduct(const Vector3 *v1, const Vector3 *v2);

/* crosses the 2 Vector3s and returns the resultant Vector3 */
Vector3 *V3_crossProduct(const Vector3 *v1, const Vector3 *v2);

/* multiplies the Vector3 by a factor and returns the result */
Vector3 *V3_multiply(Vector3 *v, float factor);

/* divides the Vector3 by a factor and returns the result */
Vector3 *V3_divide(Vector3 *v, float factor);

/* divides the Vector3 by a factor and returns the result */
Vector3 *QV3_divide(Vector3 *v, float factor);

/* calculates the magnitude of a Vector3 and returns the result */
float V3_magnitude(const Vector3 *v);

/* quickly calculates the magnitude of a Vector3 and returns the result at the cost of an error margin */
float QV3_magnitude(const Vector3 *v);

/* negates the Vector3 and returns the resultant Vector3 */
Vector3 *V3_negate(const Vector3 *v);

/* normalizes the Vector3 and returns the resultant Vector3 */
Vector3 *V3_normalize(const Vector3 *v);

/* quickly normalizes the Vector3 and returns the resultant Vector3 at the cost of an error margin */
Vector3 *QV3_normalize(const Vector3 *v);

/* get the angle btween 2 Vector3s */
float V3_angleBetween(const Vector3 *a, const Vector3 *b);

/* Get the angle made with the x axis */
float V3_angleX();

/* Get the angle made with the y axis */
float V3_angleY();

/* Get the angle made with the z axis */
float V3_angleZ();

/* returns a string to display a vector with*/
void *displayVector3();

/* Creates and assignes a new Point struct and returns it*/
Point *newPoint(float x, float y, float z);

/* assignes values to a Point struct and returns it*/
Point *P_assign(Point *p, float x, float y, float z);

/* Subtracts 2 points and returnes the result*/
Vector3 *P_subtractDontSave(const Point *a, const Point *b);

/* Adds 2 Subtracts and stores the result in the specified Point* */
Vector3 *P_subtractSave(const Point *a, const Point *b, Vector3 *saveLocation);

#define subtract(...) OVERLOAD(subtract, (__VA_ARGS__),              \
                               (P_subtractDontSave, (Point, Point)), \
                               (P_subtractSave, (Point, Point, Point)), )

/* quickly returnes the inverse of a number at the cost of an error margin */
float Q_inverse(float number);

/* quickly returnes the Square Root of a number at the cost of an error margin */
float Q_sqrt(const float number);

/* quickly returnes the inverse Square Root of a number at the cost of an error margin */
float Q_rsqrt(float number);

/*****************************************************************************************/

Vector *newVector(float value)
{
    _Node *n = (_Node *)malloc(sizeof(_Node));

    n->f_value = value;
    n->next = NULL;

    Vector *v = (Vector *)malloc(sizeof(Vector));

    v->first = n;
    v->last = n;
    v->size = 1;

    return v;
}

Vector *V_addFirst(Vector *v, float value)
{
    _Node *n = (_Node *)malloc(sizeof(_Node));

    n->f_value = value;
    n->next = v->first;

    if (v->size == 0)
    {
        v->last = n;
    }

    v->first = n;
    v->size++;
}

Vector *V_add(Vector *v, float value, int index)
{
    if (index > v->size || index < 0)
        return v;

    if (index == v->size)
        return V_addLast(v, value);

    v->size++;

    _Node *n = (_Node *)malloc(sizeof(_Node));

    n->f_value = value;
    n->next = NULL;

    if (v->size == 0)
    {
        v->first = n;
        return v;
    }

    _Node *curr = v->first;
    _Node *prev;

    for (size_t i = 0; i < v->size; i++)
    {
        if (index == 0)
        {
            n->next = v->first;
            v->first = n;
            return v;
        }
        if (i != index)
        {
            prev = curr;
            curr = curr->next;
            continue;
        }
        else
        {
            prev->next = n;
            n->next = curr;
            return v;
        }
    }
}

Vector *V_addLast(Vector *v, float value)
{
    _Node *n = (_Node *)malloc(sizeof(_Node));

    n->f_value = value;
    n->next = NULL;

    if (v->size == 0)
        v->first = n;

    v->last->next = n;
    v->last = n;
    v->size++;
}

float V_get(Vector *v, int index)
{
    if (index >= v->size || index < 0 || v->size == 0)
    {
        return -1;
    }
    if (v->size == 1)
    {
        return v->first->f_value;
    }

    _Node *curr = v->first;

    for (u_int32_t i = 0; i < v->size; i++)
    {
        if (i != index)
        {
            curr = curr->next;
            continue;
        }
        else
        {
            return curr->f_value;
        }
    }
}

Vector *V_remove(Vector *v, int index)
{

    if (index >= v->size || index < 0 || v->size == 0)
    {
        return v;
    }
    if (v->size == 1)
    {
        _Node *first = v->first;
        v->first == NULL;
        v->size--;
        free(first);
        return v;
    }

    _Node *curr;
    _Node *prev;

    for (u_int32_t i = 0; i < v->size; i++)
    {
        if (i == 0)
        {
            prev = v->first;
            if (i != index)
            {
                curr = prev->next;
                continue;
            }
            else
            {
                v->first = curr->next;
                free(curr);
                return v;
            }
        }
        else if (i != index)
        {
            prev = curr;
            curr = curr->next;
            continue;
        }
        else
        {
            prev->next = curr->next;
            free(curr);
            return v;
        }
    }
}

SortedVector *newSortedVector(float value)
{
    _DNode *n = (_DNode *)malloc(sizeof(_DNode));

    n->f_value = value;
    n->next = NULL;
    n->prev = NULL;

    SortedVector *v = (SortedVector *)malloc(sizeof(SortedVector));

    v->first = n;
    v->last = n;
    v->size = 1;
}

SortedVector *SV_add(SortedVector *v, float value)
{
    _DNode *n = (_DNode *)malloc(sizeof(_DNode));

    n->f_value = value;
    n->next = NULL;
    n->prev = NULL;

    v->size++;

    _DNode *curr;

    for (size_t i = 0; i < v->size; i++)
    {
        if (v->size == 0)
        {
            curr = v->first;
            v->first = n;
            return v;
        }
        else
        {
            if (curr->f_value <= value)
            {
                if (i != v->size - 1)
                    curr = curr->next;
                else
                    break;
            }
            else
            {
                _DNode *temp = curr->prev;
                temp->next = n;
                n->prev = curr->prev;
                n->next = curr;
                curr->prev = n;
                return v;
            }
        }
    }

    curr->next = n;

    return v;
}

float SV_get(SortedVector *v, int index)
{
    if (index >= v->size || index < 0 || v->size == 0)
    {
        return -1;
    }
    if (v->size == 1)
    {
        return v->first->f_value;
    }

    _DNode *curr = v->first;

    for (u_int32_t i = 0; i < v->size; i++)
    {
        if (i != index)
        {
            curr = curr->next;
            continue;
        }
        else
        {
            return curr->f_value;
        }
    }
}

SortedVector *SV_remove(SortedVector *v, int index)
{
    if (index >= v->size || index < 0 || v->size == 0)
    {
        return v;
    }
    if (v->size == 1)
    {
        v->first == NULL;
        v->size--;
        return v;
    }

    _DNode *prev;
    _DNode *curr;

    for (u_int32_t i = 0; i < v->size; i++)
    {
        if (i == 0)
        {
            prev = v->first;
            if (i != index)
            {
                curr = prev->next;
                continue;
            }
            else
            {
                v->first = curr->next;
                free(curr);
                return v;
            }
        }
        else if (i != index)
        {
            prev = curr;
            curr = curr->next;
            continue;
        }
        else
        {
            prev->next = curr->next;
            free(curr);
            return v;
        }
    }
}

Vector3 *newVector3(float x, float y, float z)
{
    Vector3 *v = (Vector3 *)malloc(sizeof(Vector3));

    v->x = x;
    v->y = y;
    v->z = z;

    return v;
}

Vector3 *V3_assign(Vector3 *v, float x, float y, float z)
{
    v->x = x;
    v->y = y;
    v->z = z;

    return v;
}

float V3_dotProduct(const Vector3 *v1, const Vector3 *v2)
{
    return (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
}

Vector3 *V3_crossProduct(const Vector3 *v1, const Vector3 *v2)
{
    return newVector3((v1->y * v2->z) - (v1->z * v2->y), (v1->z * v2->x) - (v1->x * v2->z), (v1->x * v2->y) - (v1->y * v2->x));
}

Vector3 *V3_multiply(Vector3 *v, float factor)
{
    v->x *= factor;
    v->y *= factor;
    v->z *= factor;
    return v;
}

Vector3 *V3_divide(Vector3 *v, float factor)
{
    v->x /= factor;
    v->y /= factor;
    v->z /= factor;
    return v;
}

Vector3 *QV3_divide(Vector3 *v, float factor)
{

    float invFactor = Q_inverse(factor);

    v->x = v->x * invFactor;
    v->y = v->y * invFactor;
    v->z = v->z * invFactor;

    return v;
}

float V3_magnitude(const Vector3 *v)
{

    return sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
}

float QV3_magnitude(const Vector3 *v)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5f;

    y = (v->x * v->x) + (v->y * v->y) + (v->z * v->z);
    x2 = y * 0.5f;

    i = *(long *)&y;

    i = 0x1FBD3F7D + (i >> 1);

    y = *(float *)&y;

    y = y * (threehalfs - (x2 * y * y));

    return y;
}

Vector3 *V3_negate(Vector3 *v)
{
    return V3_multiply(v, -1);
}

Vector3 *V3_normalize(Vector3 *v)
{
    return V3_divide(v, V3_magnitude(v));
}

Vector3 *QV3_normalize(Vector3 *v)
{
    return QV3_divide(v, QV3_magnitude(v));
}

float V3_angleBetween(const Vector3 *a, const Vector3 *b)
{
    float dot = V3_dotProduct(a, b);

    dot = (dot < -1.0 ? -1.0 : (dot > 1.0 ? 1.0 : dot));

    const float angle = acos(dot);

    return angle;
}

float V3_angleX(const Vector3 *v)
{
    return acos(v->x / V3_magnitude(v));
}

float V3_angleY(const Vector3 *v)
{
    return acos(v->y / V3_magnitude(v));
}

float V3_angleZ(const Vector3 *v)
{
    return acos(v->z / V3_magnitude(v));
}

Point *newPoint(float x, float y, float z)
{
    Point *p;

    p->x = x;
    p->y = y;
    p->z = z;

    return p;
}

Point *P_assign(Point *p, float x, float y, float z)
{
    p->x = x;
    p->y = y;
    p->z = z;

    return p;
}

Vector3 *P_subtractDontSave(const Point *a, const Point *b)
{
    Vector3 *v = (Vector3 *)malloc(sizeof(Vector3));

    v->x = a->x - b->x;
    v->y = a->y - b->y;
    v->z = a->z - b->z;

    return v;
}

Vector3 *P_subtractSave(const Point *a, const Point *b, Vector3 *saveLocation)
{
    saveLocation->x = a->x - b->x;
    saveLocation->y = a->y - b->y;
    saveLocation->z = a->z - b->z;

    return saveLocation;
}

float Q_inverse(float number)
{
    unsigned long i;
    float p0, p1;

    p0 = number;

    i = *(unsigned long *)&p0;

    i = 0x7EF4FDF3 - i;

    p0 = *(float *)&i;

    p1 = -p0 * p0 * number + 2 * p0; // newtons method

    return p1;
}

float Q_sqrt(const float number)
{
    unsigned long i;
    float p0, p1;

    p0 = number;

    i = *(unsigned long *)&p0;

    i = 0x1FBD3F7D + (i >> 1);

    p0 = *(float *)&i;

    p1 = 0.5 * (p0 + number * Q_inverse(p0)); // newtons method

    return p1;
}

float Q_rsqrt(float number)
{
    return Q_inverse(Q_sqrt(number));
}

#endif