/*
Copyright (c) 2017, Robert Krook
Copyright (c) 2017, Erik Almblad
Copyright (c) 2017, Hawre Aziz
Copyright (c) 2017, Alexander Branzell
Copyright (c) 2017, Mattias Eriksson
Copyright (c) 2017, Carl Hjerpe
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Chalmers University of Technology nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "../src/map.h"
using namespace std;
Map m;


bool assertDoubleEquals(const double one, const double two);
bool assertNodeEquals(Node one, Node two);
bool assertPolygonEquals(Polygon one, Polygon two);
bool assertMarkingEquals(Marking one, Marking two);


/* Tests on comment-lines */
bool testGoodComment() {
    string line = "# this is a comment";
    return m.isCommentLine(line);
}

bool testBadComment() {
    string line = "      # this is a bad comment, as the marking is preceeded by whitespaces";
    return !m.isCommentLine(line);
}

bool testEmptyComment() {
    string line = "";
    return !m.isCommentLine(line);
}
/* ------------------------------------------------------------------ */
/* Tests on createMarking */
bool createGoodMarking() {
    string tmp;
    ifstream in("marking.db");
    if(!in){
        cout << "Cannot open input file" << endl;
    }
    struct Marking calculatedMark;
    getline(in, tmp);
    m.createMarking(in, calculatedMark);

    struct Marking expectedMark;
    expectedMark.id = 1;
    expectedMark.x = 5;
    expectedMark.y = 5;
    return assertMarkingEquals(calculatedMark, expectedMark);
}

bool createBadMarkingEnd() {
    string tmp;
    ifstream in("badMarking.db");
    if(!in){
        cout << "Cannot open input file" << endl;
    }
    struct Marking calculatedMark;
    getline(in, tmp);
    m.createMarking(in, calculatedMark);

    struct Marking expectedMark;
    expectedMark.id = -1;
    expectedMark.x = -1;
    expectedMark.y = -1;
    return assertMarkingEquals(calculatedMark, expectedMark);
}

bool createTwoIdentical() {
    string tmp;
    ifstream in("twoIdentical.db");
    if(!in){
        cout << "Cannot open input file" << endl;
    }
    struct Marking calculatedMark1, calculatedMark2;
    getline(in, tmp);
    m.createMarking(in, calculatedMark1);

    getline(in, tmp);
    m.createMarking(in, calculatedMark2);

    struct Marking expectedMark;
    expectedMark.id = 1;
    expectedMark.x = 5;
    expectedMark.y = 5;

    bool marksequal = assertMarkingEquals(calculatedMark1, calculatedMark2);
    bool goodData   = assertMarkingEquals(calculatedMark1, expectedMark);
    return (marksequal && goodData);
}

bool createTwoDifferent() {
    string tmp;
    ifstream in("twoDifferent.db");
    if(!in){
        cout << "Cannot open input file" << endl;
    }
    struct Marking calculatedMark1, calculatedMark2;
    getline(in, tmp);
    m.createMarking(in, calculatedMark1);

    getline(in, tmp);
    m.createMarking(in, calculatedMark2);

    struct Marking expectedMark1,expectedMark2;
    expectedMark1.id = 1;
    expectedMark1.x  = 5;
    expectedMark1.y  = 5;
    expectedMark2.id = 2;
    expectedMark2.x  = 10;
    expectedMark2.y  = 10;

    bool marksequal  = !assertMarkingEquals(calculatedMark1, calculatedMark2);
    bool goodData1   = assertMarkingEquals(calculatedMark1, expectedMark1);
    bool goodData2   = assertMarkingEquals(calculatedMark2, expectedMark2);
    return (marksequal && goodData1 && goodData2);
}
/* ------------------------------------------------------------------ */
/* Tests on Nodes */
bool createGoodPoly() {
    string tmp;
    ifstream in("goodPoly.db");
    if(!in){
        cout << "Cannot open input file" << endl;
    }
    
    struct Polygon calculatedPoly;
    getline(in, tmp);
    m.createPoly(in, calculatedPoly);

    struct Polygon expectedPoly;
    expectedPoly.numOfNodes = 3;
    
    vector<Node> expnodes;
    struct Node one;   one.id   = 0; one.x   = 1; one.y   = 1;
    struct Node two;   two.id   = 1; two.x   = 2; two.y   = 2;
    struct Node three; three.id = 2; three.x = 3; three.y = 3;
    expnodes.push_back(one); expnodes.push_back(two); expnodes.push_back(three);
    expectedPoly.nodes = expnodes;

    return assertPolygonEquals(calculatedPoly, expectedPoly);
}

bool createDifferentPoly() {
    string tmp;
    ifstream in("differentPoly.db");
    if(!in){
        cout << "Cannot open input file" << endl;
    }
    
    struct Polygon calculatedPoly1, calculatedPoly2;
    getline(in, tmp);
    m.createPoly(in, calculatedPoly1);
    getline(in, tmp);
    m.createPoly(in, calculatedPoly2);

    struct Polygon expectedPoly1, expectedPoly2;
    expectedPoly1.numOfNodes = 3;
    expectedPoly2.numOfNodes = 3;
    
    vector<Node> expnodes1, expnodes2;
    struct Node one;   one.id   = 0; one.x   = 1; one.y   = 1;
    struct Node two;   two.id   = 1; two.x   = 2; two.y   = 2;
    struct Node three; three.id = 2; three.x = 3; three.y = 3;
    struct Node four;  four.id  = 0; four.x  = 4; four.y  = 4;
    struct Node five;  five.id  = 1; five.x  = 5; five.y  = 5;
    struct Node six;   six.id   = 2; six.x   = 6; six.y   = 6;
    expnodes1.push_back(one);  expnodes1.push_back(two);  expnodes1.push_back(three);
    expnodes2.push_back(four); expnodes2.push_back(five); expnodes2.push_back(six);
    expectedPoly1.nodes = expnodes1;
    expectedPoly2.nodes = expnodes2;

    bool firstEqual  =  assertPolygonEquals(calculatedPoly1, expectedPoly1);
    bool secondEqual =  assertPolygonEquals(calculatedPoly2, expectedPoly2);
    bool notSame     = !assertPolygonEquals(calculatedPoly1, calculatedPoly2);
    return (firstEqual && secondEqual && notSame);
}
bool createIdenticalPoly() {
    string tmp;
    ifstream in("identicalPoly.db");
    if(!in){
        cout << "Cannot open input file" << endl;
    }
    
    struct Polygon calculatedPoly1, calculatedPoly2;
    getline(in, tmp);
    m.createPoly(in, calculatedPoly1);
    getline(in, tmp);
    m.createPoly(in, calculatedPoly2);

    struct Polygon expectedPoly1, expectedPoly2;
    expectedPoly1.numOfNodes = 2;
    expectedPoly2.numOfNodes = 2;
    
    vector<Node> expnodes1, expnodes2;
    struct Node one;   one.id   = 0; one.x   = 1; one.y   = 1;
    struct Node two;   two.id   = 1; two.x   = 2; two.y   = 2;
    struct Node four;  four.id  = 0; four.x  = 1; four.y  = 1;
    struct Node five;  five.id  = 1; five.x  = 2; five.y  = 2;
    expnodes1.push_back(one);  expnodes1.push_back(two);
    expnodes2.push_back(four); expnodes2.push_back(five);
    expectedPoly1.nodes = expnodes1;
    expectedPoly2.nodes = expnodes2;

    bool firstEqual  =  assertPolygonEquals(calculatedPoly1, expectedPoly1);
    bool secondEqual =  assertPolygonEquals(calculatedPoly2, expectedPoly2);
    bool same     =  assertPolygonEquals(calculatedPoly1, calculatedPoly2);
    return (firstEqual && secondEqual && same);
}

bool createPolyBadEnd() {
    string tmp;
    ifstream in("polyBadEnd.db");
    if(!in){
        cout << "Cannot open input file" << endl;
    }
    
    struct Polygon calculatedPoly;
    getline(in, tmp);
    m.createPoly(in, calculatedPoly);

    struct Polygon expectedPoly;
    expectedPoly.numOfNodes = 2;
    
    vector<Node> expnodes;
    struct Node one;   one.id   = 0; one.x   = 1; one.y   = 1;
    struct Node two;   two.id   = 1; two.x   = 2; two.y   = 2;
    expnodes.push_back(one); expnodes.push_back(two);
    expectedPoly.nodes = expnodes;

    return !assertPolygonEquals(calculatedPoly, expectedPoly);
}
bool createPolyBadXY() {
    string tmp;
    ifstream in("badPolyXY.db");
    if(!in){
        cout << "Cannot open input file" << endl;
    }
    
    struct Polygon calculatedPoly;
    getline(in, tmp);
    m.createPoly(in, calculatedPoly);

    struct Polygon expectedPoly;
    expectedPoly.numOfNodes = 2;
    
    vector<Node> expnodes;
    struct Node one;   one.id   = 0; one.x   = 1; one.y   = 1;
    struct Node two;   two.id   = 1; two.x   = 2; two.y   = 2;
    expnodes.push_back(one); expnodes.push_back(two);
    expectedPoly.nodes = expnodes;

    return !assertPolygonEquals(calculatedPoly, expectedPoly);
}

/* ------------------------------------------------------------------ */
/* Tests on getMarkingPos */
bool testGoodGet() {
    int mid = 1, mx = 5, my = 5;
    struct Marking mark;
    mark.id = mid;
    mark.x = mx;
    mark.y = my;

    vector<Marking> v;
    m.markings = v;
    m.markings.push_back(mark);

    int calcx, calcy;
    m.getMarkingPos(mid, calcx, calcy);
    return (calcx == mx && calcy == my);
    
}

bool testBadGet() {
    int mid = 1, mx = 5, my = 5;
    struct Marking mark;
    mark.id = mid;
    mark.x = mx;
    mark.y = my;

    int badid = 5;

    vector<Marking> v;
    m.markings = v;
    m.markings.push_back(mark);

    int calcx, calcy;
    m.getMarkingPos(badid, calcx, calcy);
    return !(calcx == mx && calcy == my);    
}
bool testMultipleGet() {
    int mid  = 1, mx  = 5,  my  = 5;
    int m2id = 2, m2x = 10, m2y = 10;
    struct Marking mark1, mark2;
    mark1.id = mid;
    mark1.x = mx;
    mark1.y = my;
    mark2.id = m2id;
    mark2.x = m2x;
    mark2.y = m2y;

    vector<Marking> v;
    m.markings = v;
    m.markings.push_back(mark1);
    m.markings.push_back(mark2);

    int calcx1, calcy1, calcx2, calcy2;
    m.getMarkingPos(mid, calcx1, calcy1);
    m.getMarkingPos(m2id, calcx2, calcy2);
    return (calcx1 == mx && calcy1 == my && calcx2 == m2x && calcy2 == m2y);
    
}
/*
  given two doubles, returns diff < 0.000001
*/
bool assertDoubleEquals(const double one, const double two) {
    double diff = ((one - two) < 0) ? -(one - two) : (one - two); /* simple abs(one-two) */
    return (diff < 0.000001);
}

/*
  Given two Polygons, returns true if they are identical
*/
bool assertPolygonEquals(Polygon one, Polygon two) {
    if(one.numOfNodes == two.numOfNodes) {
        for(int i = 0; i < one.numOfNodes; i++) {
            if(!assertNodeEquals(one.nodes[i], two.nodes[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}

/*
  Given two Nodes, returns true if they are identical
*/
bool assertNodeEquals(Node one, Node two) {
    return one.x == two.x && one.y == two.y && one.id == two.id;
}

/*
  Given two Markings, returns true if they are identical
*/
bool assertMarkingEquals(Marking one, Marking two) {
    return one.x == two.x && one.y == two.y && one.id == two.id;
}

int main(int argc, char* argv[]) {
    cout << ((testGoodComment())        ?  "testGoodComment()     assertion holds\n" : "testGoodComment()     assertion failed\n");
    cout << ((testBadComment())         ?  "testBadComment()      assertion holds\n" : "testBadComment()      assertion failed\n");
    cout << ((testBadComment())         ?  "testEmptyComment()    assertion holds\n" : "testEmptyComment()    assertion failed\n");
    cout << ((createGoodMarking())      ?  "createGoodMarking()   assertion holds\n" : "createGoodMarking()   assertion failed\n");
    cout << ((createBadMarkingEnd())    ?  "createBadMarkingEnd() assertion holds\n" : "createBadMarkingEnd() assertion failed\n");
    cout << ((createTwoIdentical())     ?  "createTwoIdentical()  assertion holds\n" : "createTwoIdentical()  assertion failed\n");
    cout << ((createTwoDifferent())     ?  "createTwoDifferent()  assertion holds\n" : "createTwoDifferent()  assertion failed\n");
    cout << ((createGoodPoly())         ?  "createGoodPoly()      assertion holds\n" : "createGoodPoly()      assertion failed\n");
    cout << ((createDifferentPoly())    ?  "createDifferentPoly() assertion holds\n" : "createDifferentPoly() assertion failed\n");
    cout << ((createIdenticalPoly())    ?  "createIdenticalPoly() assertion holds\n" : "createIdenticalPoly() assertion failed\n");
    cout << ((createPolyBadEnd())       ?  "createPolyBadEnd()    assertion holds\n" : "createPolyBadEnd()    assertion failed\n");
    cout << ((createPolyBadXY())        ?  "createPolyBadXY()     assertion holds\n" : "createPolyBadXY()     assertion failed\n");
    cout << ((testGoodGet())            ?  "testGoodGet()         assertion holds\n" : "testGoodGet()         assertion failed\n");
    cout << ((testBadGet())             ?  "testBadGet()          assertion holds\n" : "testBadGet()          assertion failed\n");
    cout << ((testMultipleGet())        ?  "testMultipleGet()     assertion holds\n" : "testMultipleGet()     assertion failed\n");
}
