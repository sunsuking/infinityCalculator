#include "calculate.h"

pDigit minus(pDigit first, pDigit second)
{
    bool flag = false;
    bool positive = true;
    pDigit result = initializeDigit();

    if(first->beforeSize < second->beforeSize)
    {
        pDigit tmp = first;
        first = second;
        second = tmp;
        positive = false;
    }

    else if(first->beforeSize == second->beforeSize)
    {
        pNum pFirst = first->before, pSecond = second->before;
        pNum firstTmp = NULL; pNum secondTmp = NULL;
        int firstNum, secondNum;

        for(int i = 0; i < first->beforeSize; i++)
        {
            firstNum = popNum(&(first->before));
            secondNum = popNum(&(second->before));
            if(firstNum < secondNum)
            {
                flag = true;
            }
            else if(firstNum > secondNum)
            {
                flag = false;
            }
            pushNum(&firstTmp, firstNum);
            pushNum(&secondTmp, secondNum);
        }
        for(int i = 0; i < first->beforeSize; i++)
        {
            pushNum(&(first->before), popNum(&firstTmp));
            pushNum(&(second->before), popNum(&secondTmp));
        }

        if(!flag)
        {
            firstTmp = NULL; secondTmp = NULL;
            for(int i = 0; i < first->afterSize; i++)
            {
                firstNum = popNum(&(first->after));
                secondNum = popNum(&(second->after));
                if(firstNum < secondNum)
                {
                    flag = true;
                }
                pushNum(&firstTmp, firstNum);
                pushNum(&secondTmp, secondNum);
            }
            for(int i = 0; i < first->afterSize; i++)
            {
                pushNum(&(first->after), popNum(&firstTmp));
                pushNum(&(second->after), popNum(&secondTmp));
            }
        }

        if(flag)
        {
            pDigit tmp = first;
            first = second;
            second = tmp;
            positive = false;
        }
    }


//    printf("first: ");
//    returnValue(copyDigit(first));
//    printf(", second: ");
//    returnValue(copyDigit(second));
//    printf("\n");
//
//    printf("first b : %d, first a: %d", first->beforeSize, first->afterSize);
//    printf(" second b : %d, second a: %d\n", second->beforeSize, second->afterSize);


    int beforeSize = max(first->beforeSize, second->beforeSize);
    int afterSize = max(first->afterSize, second->afterSize);
    int carry=0;
    int a, b;
    pNum pfirst, psecond,presult;

    pfirst = first->after;
    psecond = second->after;
    presult = result->after;

    for (int i = 0; i < afterSize; i++) {
        if (afterSize - i > first->afterSize) {
            a = 0;
        }
        else {
            a = pfirst->num;
            pfirst = pfirst->next;
        }

        if (afterSize - i > second->afterSize) {
            b = 0;
        }
        else {
            b = psecond->num;
            psecond = psecond->next;
        }

        if (a - carry < b) {
            a = 10 + a - carry - b;
            carry = 1;
        }
        else {
            a = a - carry - b;
            carry = 0;
        }

        if (presult == NULL) {
            presult = malloc( sizeof( Num ) );
            presult->num = a;
            presult->next = NULL;
            result->after = presult;
        }
        else
        {
            presult->next = malloc( sizeof( Num ) );
            presult->next->num = a;
            presult->next->next = NULL;
            presult = presult->next;
        }
        result->afterSize++;
    }

    pfirst = first->before;
    psecond = second->before;
    presult = result->before;

    for (int i = 0; i < beforeSize; i++)
    {
        if (i >= first->beforeSize) {
            a = 0;
        }
        else {
            a = pfirst->num;
            pfirst = pfirst->next;
        }

        if (i >= second->beforeSize) {
            b = 0;
        }
        else {
            b = psecond->num;
            psecond = psecond->next;
        }

        if (a - carry < b) {
            a = 10 + a - carry - b;
            carry = 1;
        }
        else {
            a = a - carry - b;
            carry = 0;
        }

        if (presult == NULL)
        {
            presult = malloc( sizeof( Num ) );
            presult->num = a;
            presult->next = NULL;
            result->before = presult;
        }
        else {
            presult->next = malloc( sizeof( Num ) );
            presult->next->num = a;
            presult->next->next = NULL;
            presult = presult->next;
        }
        result->beforeSize++;
    }

    int end = result->afterSize;
    for (int i = 0; i < end; i++) {
        if (result->after->num == 0) {
            pNum temp = result->after->next;
            free( result->after );
            result->after = temp;
            result->afterSize--;
        }
        else {
            break;
        }
    }

//    end = result->beforeSize;
//    pNum lastNonZero = NULL;
//    pNum cur = result->before;
//    for (int i = 0; i < end; i++)
//    {
//        if (cur != NULL && cur->num != 0)
//        {
//            lastNonZero = cur;
//        }
//        cur = cur->next;
//    }
//
//    while (lastNonZero != NULL) {
//        pNum temp = lastNonZero->next;
//        lastNonZero->next = NULL;
//        if (lastNonZero->num == 0) {
//            free(lastNonZero);
//            result->beforeSize--;
//        }
//        lastNonZero = temp;
//    }

    pNum tmp = NULL;
    int tmpBeforeSize = result->beforeSize;
    for(int i = 0; i < result->beforeSize; i++)
    {
        pushNum(&tmp, popNum(&(result->before)));
    }
    if(positive)
    {
        result->positive = true;
    }
    else
    {
        result->positive = false;
    }
    for(int i = 0; i < result->beforeSize; i++)
    {

        int tmpNum = popNum(&tmp);
        if(i == (result->beforeSize - 1))
        {
           pushNum(&(result->before), tmpNum);
        }
        else
        {
            if(tmpNum != 0)
            {
                pushNum(&(result->before), tmpNum);
            }
            else
            {
                tmpBeforeSize--;
            }
        }
    }
    result->beforeSize = tmpBeforeSize;

    return result;
}