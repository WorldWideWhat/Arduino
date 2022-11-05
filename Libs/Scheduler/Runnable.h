/**
 * @file    Runnable.h
 * @author  coder@worldwidewhat.dk
 * @date    2022-10-22
 * @version 1.0
 * @brief   Runnable interface
 */

#ifndef __WORLDWIDEWHAT_RUNNABLE_H__
#define __WORLDWIDEWHAT_RUNNABLE_H__

namespace worldwidewhat
{
    class Runnable
    {
        public:
        virtual void Run() = 0;
    };
}

#endif // __WORLDWIDEWHAT_RUNNABLE_H__