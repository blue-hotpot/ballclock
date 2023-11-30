#include <stdio.h>
#include "../linkqueue/linkqueue.h"
#include "../linkqueue/linkqueue.c"
#include "../sqstack/sqstack.h"
#include "../sqstack/sqstack.c"

int check(linkqueue *lq)
{
    if(lq->front==NULL)
    {
        printf("the queue is fail");
        return -1;
    }
    nodepoint p;
    p=lq->front;
    while(p->next!=lq->rear)
    {
        if(p->data>p->next->data)
        {
            return 0;
        }
        p=p->next;
    }
    return 1;
}

int main()
{
    linkqueue *lq;
    int minute = 0;
    int breif=0;
    lq = linkqueue_creat();
    for (int i = 0; i < 27; i++)
    {
        linkqueue_in(lq, i);
    }
    sqstack *s_minute, *s_5minute, *s_hour;
    s_minute = sqstack_creat(4);
    s_5minute = sqstack_creat(11);
    s_hour = sqstack_creat(11);
    while (1)
    {
        minute++;
        if (!linkqueue_empty(lq))
        {
            //1.先考虑是否满进位，再去出球
            //2.先出球再考虑是否进位
            breif=linkqueue_out(lq);//2
            if (!sqstack_full(s_minute))
            {
                //sqstack_push(s_minute, linkqueue_out(lq));//1
                sqstack_push(s_minute, breif);//2
            }
            else
            {
                while (!sqstack_empty(s_minute))
                {
                    linkqueue_in(lq, sqstack_pop(s_minute));
                }
                if(!sqstack_full(s_5minute))
                {
                    //sqstack_push(s_5minute,linkqueue_out(lq));//1
                    sqstack_push(s_5minute,breif);//2
                }
                else
                {
                    while(!sqstack_empty(s_5minute))
                    {
                        linkqueue_in(lq,sqstack_pop(s_5minute));
                    }
                    if(!sqstack_full(s_hour))
                    {
                        //sqstack_push(s_hour,linkqueue_out(lq));//1
                        sqstack_push(s_hour,breif);//2
                    }
                    else
                    {
                        while(!sqstack_empty(s_hour))
                        {
                            linkqueue_in(lq,sqstack_pop(s_hour));
                        }
                        linkqueue_in(lq,breif);//2
                        if(check(lq)==1)
                        {
                            break;
                        }
                    }
                }
            }
        }
    }
    printf("total:%d\n",minute);
    linkqueue_show(lq);
    sqstack_free(s_minute);
    sqstack_free(s_5minute);
    sqstack_free(s_hour);
    linkqueue_free(lq);
    return 0;
}
