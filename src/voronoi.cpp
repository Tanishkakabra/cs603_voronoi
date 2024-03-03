// voronoi.cpp

// #include <cmath>
#include "voronoi.h"
#include <iostream>
using namespace std;

Voronoi::Voronoi() {}

Voronoi::~Voronoi() {}

void Voronoi::construct(const std::vector<Point> &points)
{
    cout << "Constructing Voronoi diagram" << endl;
    // Initialize event queue with leaf events
    for (long unsigned int i = 0; i < points.size(); ++i)
    {
        if (points[i].x < BOUNDminx && points[i].x != MIN_DOUBLE)
            BOUNDminx = points[i].x;
        if (points[i].x > BOUNDmaxx && points[i].x != MAX_DOUBLE)
            BOUNDmaxx = points[i].x;
        if (points[i].y < BOUNDminy && points[i].y != MIN_DOUBLE)
            BOUNDminy = points[i].y;
        if (points[i].y > BOUNDmaxy && points[i].y != MAX_DOUBLE)
            BOUNDmaxy = points[i].y;
        Q.push(points[i]);
        cout << "Bounding values: " << BOUNDminx << ", " << BOUNDmaxx << ", " << BOUNDminy << ", " << BOUNDmaxy << endl;
    }

    cout << "Queue pushed" << endl;

    BOUNDmaxx += 100;
    BOUNDminx -= 100;
    BOUNDmaxy += 100;
    BOUNDminy -= 100;
    cout << "Bounding values: " << BOUNDminx << ", " << BOUNDmaxx << ", " << BOUNDminy << ", " << BOUNDmaxy << endl;
    Point event1 = Q.top();
    sweeper = event1;
    Q.pop();
    cout << event1.x << " " << event1.y << "  HUIHUIHUIHUIHUIHUIHUI" << endl;
    Point leftmost = {MIN_DOUBLE, MAX_DOUBLE, false};
    Point rightmost = {MAX_DOUBLE, MAX_DOUBLE, false};

    T.insert({&leftmost, &event1, 0});
    T.insert({&event1, &rightmost, 0});

    while (!Q.empty())
    {
        // cout << "Before even calling site or circle event1" << endl;
        // print_Q();

        // print_Q();
        Point *newevent = new Point();
        *newevent = Q.top();
        Q.pop();
        sweeper = *newevent;

        // if (newevent->x > BOUNDmaxx && newevent->x != MAX_DOUBLE)
        //     BOUNDmaxx = newevent->x;
        // if (newevent->x < BOUNDminx && newevent->x != MIN_DOUBLE)
        //     BOUNDminx = newevent->x;
        // if (newevent->y > BOUNDmaxy && newevent->y != MAX_DOUBLE)
        //     BOUNDmaxy = newevent->y;
        // if (newevent->y < BOUNDminy && newevent->y != MIN_DOUBLE)
        //     BOUNDminy = newevent->y;

        // cout << "Before even calling site or circle event2" << endl;
        // print_T();

        // maybe an "if nullptr then continue" condition here? buggy

        cout << (*newevent).x << " " << (*newevent).y << " HUIHUIHUIHUIHUIHUI" << endl;

        if ((*newevent).isCircleEvent == 0) // site event
        {
            cout << "Site event" << endl;
            handleSiteEvent((*newevent));
        }
        else if ((*newevent).isCircleEvent == 1)
        {
            cout << "Circle event" << endl;
            handleCircleEvent((*newevent)); // Placeholder for circle event handling
        }
        // cout << "After handling event" << endl;
        print_T();
        print_Q();
        // print_circlemap();
        // delete newevent;
    }

    cout << "Finalizing diagram" << endl;
    // After processing all events, finalize the construction of the Voronoi diagram
    finalizeDiagram();
}

void Voronoi::handleSiteEvent(Point &event)
{
    if (T.empty())
    {
        cout << "OOOOOf empty tree howwww" << endl;
        return;
    }
    // cout << "Before1" << endl;
    // print_T();
    // auto it = T.upper_bound(make_pair(&event, &event));
    std::multiset<Site, ComparatorSet>::iterator next = T.upper_bound({&event, &event, 0});
    // cout << "Before1" << endl;
    if (next == T.begin())
    {
        cout << "Ummm how is this happening? Site 1" << endl;
        return;
    }
    // cout << "Next is: " << next->first->x << ", " << next->first->y << "   " << next->second->x << ", " << next->second->y << "   " << next->n << endl;

    // cout << "Before1" << endl;
    std::multiset<Site, ComparatorSet>::iterator prev = --next;
    next++;
    // cout << "Next breakpoint = " << find_breakpoint(next->first, next->second, next->n) << endl;
    // cout << "Prev breakpoint = " << find_breakpoint(prev->first, prev->second, prev->n) << endl;
    if (fabs(find_breakpoint(prev->first, prev->second, prev->n) - event.x) < 1e-4) // insert at a breakpoint itself
    {
        // cout << "Insertion at a breakpoint bro" << endl;

        // if (fabs(find_breakpoint(prev->first, &event, 0) - event.x) < 1e-4)
        //     T.insert({prev->first, &event, 0});
        // else
        //     T.insert({prev->first, &event, 1});
        // if (fabs(find_breakpoint(&event, prev->second, 0) - event.x) < 1e-4)
        //     T.insert({&event, prev->second, 0});
        // else
        //     T.insert({&event, prev->second, 1});

        // Point *q = findLeaf(next, prev);
        // Point *edgeval = new Point();
        // *edgeval = {event.x, parabola_at_x(q), 0};
        // add_edge({prev->first, prev->second, prev->n}, edgeval);
        // add_edge({prev->first, &event, 0}, edgeval);
        // add_edge({prev->first, &event, 1}, edgeval);

        // std::multiset<Site, ComparatorSet>::iterator prev2 = --prev;
        // prev++;
        // Point *p = findLeaf(prev2, prev);
        // Point *pl;
        // if (prev2->first == p)
        //     pl = prev2->second;
        // else
        //     pl = prev2->first;
        // Point *pr;

        // if (next->first == q)
        //     pr = next->second;
        // else
        //     pr = next->first;

        // Point circ = find_circumcentre(p, q, &event);
        // if (circ.isCircleEvent == 1 && circlemap[{prev->first, &event, prev->second}] != -1)
        // {
        //     Q.push(circ);
        //     circlemap[{prev->first, &event, prev->second}] = 1;
        // }
        // Point circ2 = find_circumcentre(pl, p, &event);
        // if (circ2.isCircleEvent == 1 && circlemap[{pl, p, &event}] != -1)
        // {
        //     Q.push(circ2);
        //     circlemap[{pl, p, &event}] = 1;
        // }
        // Point circ3 = find_circumcentre(&event, q, pr);
        // if (circ3.isCircleEvent == 1 && circlemap[{&event, q, pr}] != -1)
        // {
        //     Q.push(circ3);
        //     circlemap[{&event, q, pr}] = 1;
        // }
        // T.erase(prev);
        // return;
    }
    // cout << "Prev is: " << prev->first->x << ", " << prev->first->y << "   " << prev->second->x << ", " << prev->second->y << "   " << prev->n << endl;
    // cout << "Before2" << endl;
    Point *q = findLeaf(next, prev);
    // cout << "Before2" << endl;
    Point *pl;
    if (prev->first == q)
        pl = prev->second;
    else
        pl = prev->first;
    // cout << "Before3" << endl;
    Point *pr;
    if (next->first == q)
        pr = next->second;
    else
        pr = next->first;
    // cout << "Next is: " << next->first->x << ", " << next->first->y << "   " << next->second->x << ", " << next->second->y << "   " << next->n << endl;
    // cout << "Prev is: " << prev->first->x << ", " << prev->first->y << "   " << prev->second->x << ", " << prev->second->y << "   " << prev->n << endl;
    // print_T();
    // cout << "pl q pr found in site handling" << endl;
    // cout << pl->x << ", " << pl->y << "   " << q->x << ", " << q->y << "   " << pr->x << ", " << pr->y << endl;
    // cout << "Pehle ki kahani" << endl;
    // cout << pl->x << ", " << pl->y << "   " << q->x << ", " << q->y << "   " << pr->x << ", " << pr->y << endl;
    // cout << "Before" << endl;
    // print_T();
    // cout << event.x << "," << event.y << endl;

    // circlemap[{pl, q, pr}] = 0;

    // inserted a new site huihuihui. 0 and 1 for both combinations hehe
    double m = (q->y - event.y) / (-q->x + event.x);
    if (m > 0)
    {
        T.insert({q, &event, 0});
        T.insert({q, &event, 1});
    }
    else
    {
        T.insert({q, &event, 1});
        T.insert({q, &event, 0});
    }

    Point *edgeval = new Point();
    *edgeval = {event.x, parabola_at_x(q), 0};
    add_edge({q, &event, 0}, edgeval);
    add_edge({q, &event, 1}, edgeval);
    // cout << "After after" << endl;
    // print_T();
    // cout << "finding circle: " << pl->x << ", " << pl->y << "   " << q->x << ", " << q->y << "   " << event.x << ", " << event.y << endl;
    Point circ = find_circumcentre(pl, q, &event);
    // cout << "Circle coordinates be like: " << circ.x << ", " << circ.y << endl;
    if (circ.isCircleEvent == 1 && circlemap[{pl, q, &event}] != -1)
    {
        cout << "Watch my circle coordinates" << endl;
        cout << circ.x << ", " << circ.y << endl;
        Q.push(circ);
        // cout << "Before circlemap" << endl;
        // print_circlemap();
        circlemap[{pl, q, &event}] = 1;
        // cout << "After circlemap" << endl;
        // print_circlemap();
    }
    // cout << "MEOWMEOWMEOWMEOWMEOWMEOWMEOWMMEOJDIUWCWBCUBVUUUUUUUUUUUUUUUUUUU" << endl;
    Point circ2 = find_circumcentre(&event, q, pr);
    // cout << Point circ2 = find_circumcentre(&event, q, pr);
    // cout << "Circle coordinates be like: " << circ2.x << ", " << circ2.y << endl;
    if (circ2.isCircleEvent == 1 && !(circ2.x == circ.x && circ2.y == circ.y && circ2.isCircleEvent == circ.isCircleEvent) && circlemap[{&event, q, pr}] != -1)
    {
        cout << "Watch my circle coordinates" << endl;
        cout << circ2.x << ", " << circ2.y << endl;
        Q.push(circ2);
        // cout << "Before circlemap" << endl;
        // print_circlemap();
        circlemap[{&event, q, pr}] = 1;
        // cout << "After circlemap" << endl;
        // print_circlemap();
    }
    // cout << "Before even calling site or circle event from handlesiteevent" << endl;
    // print_T();
    return;
    // if pr and pl are different, there mustve been a circle event associated with them.
    // perhaps in a map huihuihui
}

void Voronoi::handleCircleEvent(Point &event)
{
    cout << "Handling circle event yayyyyyy Lets find out the bugs now shall we?" << endl;
    // print_T();
    // print_circlemap();
    std::multiset<Site, ComparatorSet>::iterator next = T.upper_bound({&event, &event, 0});
    // cout << "Next for circle event is" << endl;
    // cout << next->first->x << ", " << next->first->y << "   " << next->second->x << ", " << next->second->y << "   " << next->n << endl;
    if (next == T.begin())
    {
        // cout << next->first->x << ", " << next->first->y << "   " << next->second->x << ", " << next->second->y << "   " << next->n << endl;
        // find_breakpoint(next->first, next->second, 2);
        cout << "Ummm how is this happening? Circle 1" << endl;
        return;
    }

    std::multiset<Site, ComparatorSet>::iterator curr = --next;
    next++;
    if (curr == T.begin())
    {
        // cout << next->first->x << ", " << next->first->y << "   " << next->second->x << ", " << next->second->y << "   " << next->n << endl;
        // cout << curr->first->x << ", " << curr->first->y << "   " << curr->second->x << ", " << curr->second->y << "   " << curr->n << endl;
        // find_breakpoint(curr->first, curr->second, 2);
        cout << "Ummm how is this happening? Circle 2" << endl;
        return;
    }
    std::multiset<Site, ComparatorSet>::iterator prev = --curr; // prev and curr converge, next ki zarurat nhi i think
    curr++;

    // to call out false alarms
    if (fabs(find_breakpoint(prev->first, prev->second, prev->n) - event.x) > 1e-4 || fabs(find_breakpoint(curr->first, curr->second, curr->n) - event.x) > 1e-4)
    {
        cout << "FALSE ALARM I REPEAT FALSE ALARM AAAAAAA" << endl;
        cout << prev->first->x << ", " << prev->first->y << "   " << prev->second->x << ", " << prev->second->y << "   " << prev->n << endl;
        cout << find_breakpoint(prev->first, prev->second, prev->n) << endl;
        cout << curr->first->x << ", " << curr->first->y << "   " << curr->second->x << ", " << curr->second->y << "   " << curr->n << endl;
        cout << find_breakpoint(curr->first, curr->second, curr->n) << endl;
        cout << next->first->x << ", " << next->first->y << "   " << next->second->x << ", " << next->second->y << "   " << next->n << endl;
        cout << find_breakpoint(next->first, next->second, next->n) << endl;
        cout << "Event mera x: " << event.x << endl;
        cout << "Ummm how is this happening? False alarm" << endl;
        return;
    }
    // cout << "Event.x = " << event.x << endl;
    // cout << prev->first->x << ", " << prev->first->y << "   " << prev->second->x << ", " << prev->second->y << "   " << prev->n << endl;
    // cout << find_breakpoint(prev->first, prev->second, prev->n) << endl;
    // cout << curr->first->x << ", " << curr->first->y << "   " << curr->second->x << ", " << curr->second->y << "   " << curr->n << endl;
    // cout << find_breakpoint(curr->first, curr->second, curr->n) << endl;
    // cout << next->first->x << ", " << next->first->y << "   " << next->second->x << ", " << next->second->y << "   " << next->n << endl;
    // cout << find_breakpoint(next->first, next->second, next->n) << endl;

    Point *q = findLeaf(curr, prev);

    Point *pl;
    if (prev->first == q)
        pl = prev->second;
    else
        pl = prev->first;
    Point *pr;
    if (curr->first == q)
        pr = curr->second;
    else
        pr = curr->first;
    // q disappears, pr and pl remain.
    cout << "pl q pr found" << endl;
    cout << pl->x << ", " << pl->y << "   " << q->x << ", " << q->y << "   " << pr->x << ", " << pr->y << endl;
    if (circlemap[{pl, q, pr}] != 1) // if the circle event is false alarm, then dont do anything
        return;
    if (pl->x == MAX_DOUBLE || pl->x == MIN_DOUBLE || pr->x == MAX_DOUBLE || pr->x == MIN_DOUBLE || q->x == MAX_DOUBLE || q->x == MIN_DOUBLE)
    {
        cout << "Ummm how is this happening? Circle 3" << endl;
        return;
    }

    Point *edgeval = new Point();
    *edgeval = {event.x, parabola_at_x((*prev).first), 0};
    add_edge(*prev, edgeval);
    add_edge(*curr, edgeval);

    // Lets try being buggy
    cout << "Circle event is valid" << endl;
    // add_to_edge_map(pl, q, pr, &event);
    // cout << "About to erase shit" << endl;
    // cout << prev->first->x << ", " << prev->first->y << "   " << prev->second->x << ", " << prev->second->y << "   " << prev->n << endl;
    // cout << find_breakpoint(prev->first, prev->second, prev->n) << endl;
    // cout << curr->first->x << ", " << curr->first->y << "   " << curr->second->x << ", " << curr->second->y << "   " << curr->n << endl;
    // cout << find_breakpoint(curr->first, curr->second, curr->n) << endl;
    T.erase(curr);
    T.erase(prev);
    // cout << "Erased" << endl;
    Site s;
    // cout << "Purely for debugging purposes0" << endl;
    // print_T();
    // cout << "Trying to add a new node" << endl;
    if (fabs(find_breakpoint(pl, pr, 0) - event.x) < 1e-4) // delete the 2 nodes and introduce 1 node instead.
    {
        // cout << "Ill let you know when i get here 0" << endl;
        s = {pl, pr, 0};
        T.insert(s);
    }
    else if (fabs(find_breakpoint(pl, pr, 1) - event.x) < 1e-4)
    {
        // cout << "Ill let you know when i get here 1" << endl;
        s = {pl, pr, 1};
        T.insert(s);
    }
    else
    {
        cout << "Ummm how the hap is this evening?" << endl;
    }
    // cout << "Purely for debugging purposes1" << endl;
    // print_T();
    add_edge(s, edgeval);
    circlemap[{pl, q, pr}] = -1;
    next = T.upper_bound(s);
    if (next == T.begin())
    {
        // cout << "Ummm how is this happening? Circle 4" << endl;
        return;
    }

    curr = --next;
    if (curr == T.begin())
    {
        // cout << "Ummm how is this happening? Circle 5" << endl;
        return;
    }
    next++;
    prev = --curr;

    curr++;
    // std::set<Site, ComparatorSet>::iterator prev2 = --prev;
    // // prev++;
    // cout << "I'm here3" << endl;
    // cout << "check new circle events between next curr and prev curr and the new node" << endl;
    // cout << prev2->first->x << ", " << prev2->first->y << "   " << prev2->second->x << ", " << prev2->second->y << "   " << prev2->n << endl;
    // cout << find_breakpoint(prev2->first, prev2->second, prev2->n) << endl;
    // cout << s.first->x << ", " << s.first->y << "   " << s.second->x << ", " << s.second->y << "   " << s.n << endl;
    // cout << find_breakpoint(s.first, s.second, s.n) << endl;
    // cout << prev->first->x << ", " << prev->first->y << "   " << prev->second->x << ", " << prev->second->y << "   " << prev->n << endl;
    // cout << find_breakpoint(prev->first, prev->second, prev->n) << endl;
    // cout << curr->first->x << ", " << curr->first->y << "   " << curr->second->x << ", " << curr->second->y << "   " << curr->n << endl;
    // cout << find_breakpoint(curr->first, curr->second, curr->n) << endl;
    // cout << next->first->x << ", " << next->first->y << "   " << next->second->x << ", " << next->second->y << "   " << next->n << endl;
    // cout << find_breakpoint(next->first, next->second, next->n) << endl;
    // print_T();
    // check new circle events between next curr and prev curr
    //                        prev  curr  next
    // let prev curr next = pll2  pl2   q2   pr2
    // cout << "Adding new circle events" << endl;
    Point *q2 = findLeaf(next, curr);
    // cout << "pll2 pl2 q2 pr2" << endl;
    Point *pl2;
    if (curr->first == q2)
        pl2 = curr->second;
    else
        pl2 = curr->first;
    // cout << "pll2 pl2 q2 pr2" << endl;
    Point *pr2;
    if (next->first == q2)
        pr2 = next->second;
    else
        pr2 = next->first;
    // cout << "pll2 pl2 q2 pr2" << endl;
    Point *pll2;
    if (prev->first == pl2)
        pll2 = prev->second;
    else
        pll2 = prev->first;

    cout << "pll2 pl2 q2 pr2" << endl;

    Point circ = find_circumcentre(pl2, q2, pr2);

    if (circ.isCircleEvent == 1 && circlemap[{pl2, q2, pr2}] != -1)
    {
        Q.push(circ);
        cout << "Watch my circle eventt" << endl;
        cout << circ.x << ", " << circ.y << endl;
        // cout << "pl2 q2 pr2" << endl;
        // cout << pl2->x << ", " << pl2->y << "   " << q2->x << ", " << q2->y << "   " << pr2->x << ", " << pr2->y << endl;
        // print_circlemap();
        circlemap[{pl2, q2, pr2}] = 1;
        // cout << "After circlemapc1" << endl;
        // print_circlemap();
    }

    Point circ2 = find_circumcentre(pll2, pl2, q2);
    if (circ2.isCircleEvent == 1 && circlemap[{pll2, pl2, q2}] != -1 && !(circ2.x == circ.x && circ2.y == circ.y && circ2.isCircleEvent == circ.isCircleEvent))
    {
        Q.push(circ2);
        cout << "Watch my circle eventt" << endl;
        cout << circ2.x << ", " << circ2.y << endl;
        // cout << "pll2 pl2 q2" << endl;
        // cout << pll2->x << ", " << pll2->y << "   " << pl2->x << ", " << pl2->y << "   " << q2->x << ", " << q2->y << endl;
        // print_circlemap();
        circlemap[{pll2, pl2, q2}] = 1;
        // cout << "After circlemapc2" << endl;
        // print_circlemap();
    }

    // need to add new circle events i suppose, done i hope
    // bc ye kya circle event kar rhi hu mai, i dont think the circlemap works like its supposed to.

    // Implementation of circle event handling
    // (You need to implement this function)
}

void Voronoi::add_edge(Site s, Point *event)
{
    if (edgemap[s].start == nullptr)
    {
        cout << "Edge Starts:  " << event->x << ", " << event->y << endl;
        edgemap[s].start = event;
    }
    else if (edgemap[s].end == nullptr)
    {
        edgemap[s].end = event;
        cout << "Edge ends:  " << edgemap[s].start->x << ", " << edgemap[s].start->y << "   " << edgemap[s].end->x << ", " << edgemap[s].end->y << endl;
    }
    else
    {
        cout << "UMMM how is this happening? edgemap error" << endl;
    }
}

void Voronoi::finalizeDiagram()
{
    cout << "Finalizing diagram in finaliseDiagram" << endl;
    int i = 0;
    // iterate over edgemap and create DCEL
    // sweeper.y;
    for (auto it = edgemap.begin(); it != edgemap.end(); it++)
    {
        cout << i++ << " map entries" << endl;
        if (it->second.start != nullptr && it->second.end != nullptr) // complete edge
        {
            // cout << it->first.first->x << ", " << it->first.first->y << "   " << it->first.second->x << ", " << it->first.second->y << endl;
            // cout << it->second.start->x << ", " << it->second.start->y << "   " << it->second.end->x << ", " << it->second.end->y << endl;

            edgelist.push_back(make_pair(it->second.start, it->second.end));
        }
        else if (it->second.start != nullptr && it->second.end == nullptr) // half edge
        {
            Point *p = new Point();
            *p = find_bound_box_intersection(it->first, it->second);
            it->second.end = p;
            // cout << "Found bound box intersection: ";
            // cout << p->x << ", " << p->y << endl;
            // cout << it->second.start->x << ", " << it->second.start->y << endl;
            // cout << it->second.end->x << ", " << it->second.end->y << endl;
            // cout << it->first.first->x << ", " << it->first.first->y << "   " << it->first.second->x << ", " << it->first.second->y << endl;
            edgelist.push_back(make_pair(it->second.start, it->second.end));
        }
        else
        {
            cout << "UMMM how is this happening?" << endl;
        }
    }
    cout << "Bounding values: " << BOUNDminx << ", " << BOUNDmaxx << ", " << BOUNDminy << ", " << BOUNDmaxy << endl;
}

double Voronoi::parabola_at_x(Point *p)
{
    double x1 = p->x;
    double y1 = p->y;
    double h = sweeper.y;
    double x = sweeper.x;

    return ((x - x1) * (x - x1) + y1 * y1 - h * h) / (2 * y1 - 2 * h);
}

double Voronoi::parabolaatx(Point *p, double x)
{
    double x1 = p->x;
    double y1 = p->y;
    double h = sweeper.y;

    return ((x - x1) * (x - x1) + y1 * y1 - h * h) / (2 * y1 - 2 * h);
}

Point *Voronoi::findLeaf(std::multiset<Site, ComparatorSet>::iterator next, std::multiset<Site, ComparatorSet>::iterator prev)
{
    if (next->first == prev->first && next->second == prev->second)
    {
        // p,q and q,p wala case.
        if (parabola_at_x(next->first) < parabola_at_x(next->second))
            return next->first;
        else
            return next->second;
    }
    else if (next->first == prev->second && next->second == prev->first)
    { // unlikely
        cout << "UMMM how is this happening?" << endl;
        if (parabola_at_x(next->first) < parabola_at_x(next->second))
            return next->first;
        else
            return next->second;
    }
    else if (next->first->x == prev->first->x && next->first->y == prev->first->y)
        return next->first;
    else if (next->first->x == prev->second->x && next->first->y == prev->second->y)
        return next->first;
    else if (next->second->x == prev->first->x && next->second->y == prev->first->y)
        return next->second;
    else if (next->second->x == prev->second->x && next->second->y == prev->second->y)
        return next->second;
    else
    {
        cout << "Nothing in common? how strange." << endl;
    }
    return nullptr;
}

Point Voronoi::find_bound_box_intersection(Site s, EdgeData edge)
{
    // calculate perpendicular bisector of the 2 points
    Point *p = s.first;
    Point *q = s.second; // p and q are the 2 points for which i need to find perpendicular bisector.
    // Point *r = edge.vertex3;
    double x = find_breakpoint(p, q, s.n);
    double y = parabolaatx(p, x);
    edge.end = new Point();
    edge.end->x = x;
    edge.end->y = y;
    if (x == 0 && y == 0)
        cout << "Panik! found the 0000000000000000000000000000000000000000000000000" << endl;
    // if (x > BOUNDmaxx)
    // {
    //     x = BOUNDmaxx;
    //     y = edge.start->y + x * (edge.end->y - edge.start->y) / (edge.end->x - edge.start->x);
    // }
    // else if (x < BOUNDminx)
    // {
    //     x = BOUNDminx;
    //     y = edge.start->y + x * (edge.end->y - edge.start->y) / (edge.end->x - edge.start->x);
    // }
    // else if (y > BOUNDmaxy)
    // {
    //     y = BOUNDmaxy;
    //     x = edge.start->x + y * (edge.end->x - edge.start->x) / (edge.end->y - edge.start->y);
    // }
    // else if (y < BOUNDminy)
    // {
    //     y = BOUNDminy;
    //     x = edge.start->x + y * (edge.end->x - edge.start->x) / (edge.end->y - edge.start->y);
    // }
    return {x, y, false};
}

void Voronoi::print_edgemap()
{
    for (auto it = edgemap.begin(); it != edgemap.end(); it++)
    {
        cout << "Edge: Start: " << it->second.start->x << ", " << it->second.start->y << " End: " << it->second.end->x << ", " << it->second.end->y << endl;
    }
}

void Voronoi::print_circlemap()
{
    for (auto it = circlemap.begin(); it != circlemap.end(); it++)
    {
        for (auto it2 = it->first.begin(); it2 != it->first.end(); it2++)
        {
            cout << (*it2)->x << ", " << (*it2)->y << "       ";
        }
        cout << " Value: " << it->second << endl;
    }
}

void Voronoi::print_Q()
{
    priority_queue<Point, vector<Point>, ComparatorQueue> temp = Q;
    while (!temp.empty())
    {
        cout << "Point: " << (temp.top()).x << ", " << (temp.top().y) << endl;
        temp.pop();
    }
}

void Voronoi::print_T()
{
    for (auto it = T.begin(); it != T.end(); it++)
    {
        cout << "Site: " << (it->first)->x << ", " << (it->first)->y << "    " << (it->second)->x << ", " << (it->second)->y << " " << it->n << endl;
        cout << find_breakpoint(it->first, it->second, it->n) << endl;
        // cout << sweeper.y << endl;
    }
}