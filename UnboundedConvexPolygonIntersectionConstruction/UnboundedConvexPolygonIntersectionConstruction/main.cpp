#include "UnboundedConvexPolygonIntersectionConstruction.h"

void print(Point& p) {
	std::cout << "(" << p.x << ", " << p.y << ")";
}

void print(Halfplane& hp) {
	print(hp.first);
	std::cout << " ";
	print(hp.second);
	std::cout << std::endl;
}

void print(std::vector<Halfplane>& P) {
	for (int i = 0; i < P.size(); i++) {
		print(P[i]);
	}
}

double area2(Point& p, Point& q, Point& r) {
	return p.x * q.y - p.y * q.x + q.x * r.y - q.y * r.x + r.x * p.y - r.y * p.x;
}

bool toLeft(Point& p, Point& q, Point& r) {
	return area2(p, q, r) > 0;
}

Point intersectionPoint(Halfplane& hp1, Halfplane& hp2) {
	double a1 = area2(hp1.first, hp2.first, hp2.second);
	double a2 = area2(hp1.second, hp2.first, hp2.second);
	Point p;
	p.x = a2 / (a2 - a1) * hp1.first.x + a1 / (a1 - a2) * hp1.second.x;
	p.y = a2 / (a2 - a1) * hp1.first.y + a1 / (a1 - a2) * hp1.second.y;
	return p;
}

bool inConvexPolygon(std::vector<Halfplane>& P, Point& p, int index1, int index2) {
	for (int i = 0; i < P.size(); i++) {
		if (i != index1 && i != index2) {
			if (!toLeft(P[i].first, P[i].second, p)) {
				return false;
			}
		}
	}
	return true;
}

bool isBounded(std::vector<Halfplane>& P) {
	if (P.empty()) {
		return true;
	}
	if (P.size() == 1 || P.size() == 2) {
		return false;
	}
	Point p = intersectionPoint(P[0], P[P.size() - 1]);
	if (inConvexPolygon(P, p, 0, P.size() - 1)) {
		return true;
	}
	else {
		return false;
	}
}

bool isSame(std::vector<std::vector<Halfplane>>& P) {
	for (int i = 1; i < P.size(); i++) {
		if (P[0].size() != P[i].size()) {
			return false;
		}
		if (isBounded(P[0])) {
			int index = -1;
			for (int j = 0; j < P[0].size(); j++) {
				if (P[0][0] == P[i][j]) {
					index = j;
					break;
				}
			}
			if (!P[0].empty() && index == -1) {
				return false;
			}
			for (int j = 0; j < P[0].size(); j++) {
				if (!(P[0][j] == P[i][(index + j) % P[0].size()])) {
					return false;
				}
			}
		}
		else {
			for (int j = 0; j < P[0].size(); j++) {
				if (!(P[0][j] == P[i][j])) {
					return false;
				}
			}
		}
	}
	return true;
}

void generateUnboundedConvexPolygon(std::vector<std::vector<Halfplane>>& P1, std::vector<std::vector<Halfplane>>& P2) {
	Halfplane hp;
	Point p;
	P1.push_back(std::vector<Halfplane>());
	p.x = 0.457811755491793; p.y = 0.8864318858756868; hp.first = p;
	p.x = 0.7803096308075329; p.y = 0.3230041882646719; hp.second = p;
	P1[0].push_back(hp);
	p.x = 0.7803096308075329; p.y = 0.3230041882646719; hp.first = p;
	p.x = 0.6396625990317838; p.y = 0.6013507242143026; hp.second = p;
	P1[0].push_back(hp);
	p.x = 0.6396625990317838; p.y = 0.6013507242143026; hp.first = p;
	p.x = 0.5880566821454367; p.y = 0.7009007535241197; hp.second = p;
	P1[0].push_back(hp);
	p.x = 0.5880566821454367; p.y = 0.7009007535241197; hp.first = p;
	p.x = 0.2712560931910786; p.y = 1.2588672738742077; hp.second = p;
	P1[0].push_back(hp);
	p.x = 0.2712560931910786; p.y = 1.2588672738742077; hp.first = p;
	p.x = 0.03413915668268014; p.y = 1.6755949737184936; hp.second = p;
	P1[0].push_back(hp);
	p.x = 0.03413915668268014; p.y = 1.6755949737184936; hp.first = p;
	p.x = -0.10567455156049146; p.y = 1.920784177408507; hp.second = p;
	P1[0].push_back(hp);
	p.x = -0.10567455156049146; p.y = 1.920784177408507; hp.first = p;
	p.x = -0.34205537632543387; p.y = 2.334259224640123; hp.second = p;
	P1[0].push_back(hp);
	p.x = -0.34205537632543387; p.y = 2.334259224640123; hp.first = p;
	p.x = -0.6529732883406629; p.y = 2.8777936402889606; hp.second = p;
	P1[0].push_back(hp);
	p.x = -0.6529732883406629; p.y = 2.8777936402889606; hp.first = p;
	p.x = -0.9045480881753829; p.y = 3.317339071136182; hp.second = p;
	P1[0].push_back(hp);
	p.x = -0.9045480881753829; p.y = 3.317339071136182; hp.first = p;
	p.x = -1.0431360951868953; p.y = 3.559465682274003; hp.second = p;
	P1[0].push_back(hp);
	P2.push_back(std::vector<Halfplane>());
	p.x = 0.05185339753225171; p.y = 0.8122935229416867; hp.first = p;
	p.x = 0.6001174447640614; p.y = 0.3233214000004929; hp.second = p;
	P2[0].push_back(hp);
	p.x = 0.6001174447640614; p.y = 0.3233214000004929; hp.first = p;
	p.x = 0.9262693830793078; p.y = 0.3805455361904426; hp.second = p;
	P2[0].push_back(hp);
	p.x = 0.9262693830793078; p.y = 0.3805455361904426; hp.first = p;
	p.x = 0.7311168447399099; p.y = 0.7435958044275699; hp.second = p;
	P2[0].push_back(hp);
	p.x = 0.7311168447399099; p.y = 0.7435958044275699; hp.first = p;
	p.x = 0.497301786195784; p.y = 1.1253363393941926; hp.second = p;
	P2[0].push_back(hp);
	p.x = 0.497301786195784; p.y = 1.1253363393941926; hp.first = p;
	p.x = 0.35865652119063296; p.y = 1.3289337164730712; hp.second = p;
	P2[0].push_back(hp);
	p.x = 0.35865652119063296; p.y = 1.3289337164730712; hp.first = p;
	p.x = 0.2560792056826452; p.y = 1.443030522135609; hp.second = p;
	P2[0].push_back(hp);
	p.x = 0.2560792056826452; p.y = 1.443030522135609; hp.first = p;
	p.x = 0.1610647414541373; p.y = 1.5306962267833284; hp.second = p;
	P2[0].push_back(hp);
	p.x = 0.1610647414541373; p.y = 1.5306962267833284; hp.first = p;
	p.x = 0.04604442799520777; p.y = 1.6347255444755853; hp.second = p;
	P2[0].push_back(hp);
	p.x = 0.04604442799520777; p.y = 1.6347255444755853; hp.first = p;
	p.x = -0.043831895620835705; p.y = 1.7153391549257173; hp.second = p;
	P2[0].push_back(hp);
	p.x = -0.043831895620835705; p.y = 1.7153391549257173; hp.first = p;
	p.x = -0.4089026392084431; p.y = 2.041380603995541; hp.second = p;
	P2[0].push_back(hp);
	P1.push_back(std::vector<Halfplane>());
	p.x = 0.9780137419136107; p.y = 0.6775856031989764; hp.first = p;
	p.x = 0.9762506293811978; p.y = 0.21604059252568364; hp.second = p;
	P1[1].push_back(hp);
	p.x = 0.9762506293811978; p.y = 0.21604059252568364; hp.first = p;
	p.x = 0.9829955279942372; p.y = 0.752277822039966; hp.second = p;
	P1[1].push_back(hp);
	p.x = 0.9829955279942372; p.y = 0.752277822039966; hp.first = p;
	p.x = 0.9903381087449442; p.y = 1.5275691160003775; hp.second = p;
	P1[1].push_back(hp);
	p.x = 0.9903381087449442; p.y = 1.5275691160003775; hp.first = p;
	p.x = 0.9949438834772784; p.y = 2.1699061640578385; hp.second = p;
	P1[1].push_back(hp);
	p.x = 0.9949438834772784; p.y = 2.1699061640578385; hp.first = p;
	p.x = 0.9992912788383124; p.y = 2.930430807767956; hp.second = p;
	P1[1].push_back(hp);
	p.x = 0.9992912788383124; p.y = 2.930430807767956; hp.first = p;
	p.x = 1.002047869530905; p.y = 3.5410076086084534; hp.second = p;
	P1[1].push_back(hp);
	p.x = 1.002047869530905; p.y = 3.5410076086084534; hp.first = p;
	p.x = 1.005759902313233; p.y = 4.404123131061399; hp.second = p;
	P1[1].push_back(hp);
	p.x = 1.005759902313233; p.y = 4.404123131061399; hp.first = p;
	p.x = 1.0102814014157158; p.y = 5.486897766414735; hp.second = p;
	P1[1].push_back(hp);
	p.x = 1.0102814014157158; p.y = 5.486897766414735; hp.first = p;
	p.x = 1.0137946155984132; p.y = 6.328666227155422; hp.second = p;
	P1[1].push_back(hp);
	p.x = 1.0137946155984132; p.y = 6.328666227155422; hp.first = p;
	p.x = 1.0175262709642108; p.y = 7.249935193037089; hp.second = p;
	P1[1].push_back(hp);
	P2.push_back(std::vector<Halfplane>());
	p.x = 0.7582091548463749; p.y = 0.8744560957317553; hp.first = p;
	p.x = 0.6893263772366388; p.y = 0.010086142493833328; hp.second = p;
	P2[1].push_back(hp);
	p.x = 0.6893263772366388; p.y = 0.010086142493833328; hp.first = p;
	p.x = 0.9770713806818657; p.y = 0.6126736425381352; hp.second = p;
	P2[1].push_back(hp);
	p.x = 0.9770713806818657; p.y = 0.6126736425381352; hp.first = p;
	p.x = 1.0759175368282974; p.y = 1.2158440492099827; hp.second = p;
	P2[1].push_back(hp);
	p.x = 1.0759175368282974; p.y = 1.2158440492099827; hp.first = p;
	p.x = 1.152806617461396; p.y = 1.9648436253566393; hp.second = p;
	P2[1].push_back(hp);
	p.x = 1.152806617461396; p.y = 1.9648436253566393; hp.first = p;
	p.x = 1.204086544724107; p.y = 2.5984808340223506; hp.second = p;
	P2[1].push_back(hp);
	p.x = 1.204086544724107; p.y = 2.5984808340223506; hp.first = p;
	p.x = 1.2568609359235041; p.y = 3.259495725165789; hp.second = p;
	P2[1].push_back(hp);
	p.x = 1.2568609359235041; p.y = 3.259495725165789; hp.first = p;
	p.x = 1.3202613565275096; p.y = 4.054651548315162; hp.second = p;
	P2[1].push_back(hp);
	p.x = 1.3202613565275096; p.y = 4.054651548315162; hp.first = p;
	p.x = 1.444308401756263; p.y = 5.610846802014908; hp.second = p;
	P2[1].push_back(hp);
	p.x = 1.444308401756263; p.y = 5.610846802014908; hp.first = p;
	p.x = 1.5413144436514663; p.y = 6.827836808065705; hp.second = p;
	P2[1].push_back(hp);
	p.x = 1.5413144436514663; p.y = 6.827836808065705; hp.first = p;
	p.x = 1.6503150978081065; p.y = 8.195457152096091; hp.second = p;
	P2[1].push_back(hp);
	P1.push_back(std::vector<Halfplane>());
	p.x = 0.4623685558240215; p.y = 0.10738708973868838; hp.first = p;
	p.x = 0.3023620576862479; p.y = 0.5032785115171143; hp.second = p;
	P1[2].push_back(hp);
	p.x = 0.3023620576862479; p.y = 0.5032785115171143; hp.first = p;
	p.x = 0.04219008076238728; p.y = 0.5173483162831487; hp.second = p;
	P1[2].push_back(hp);
	p.x = 0.04219008076238728; p.y = 0.5173483162831487; hp.first = p;
	p.x = -0.17775105227796012; p.y = 0.47680388077695524; hp.second = p;
	P1[2].push_back(hp);
	p.x = -0.17775105227796012; p.y = 0.47680388077695524; hp.first = p;
	p.x = -0.2361637869715853; p.y = 0.45504667315139313; hp.second = p;
	P1[2].push_back(hp);
	p.x = -0.2361637869715853; p.y = 0.45504667315139313; hp.first = p;
	p.x = -0.2074233391913236; p.y = 0.3236115327181553; hp.second = p;
	P1[2].push_back(hp);
	p.x = -0.2074233391913236; p.y = 0.3236115327181553; hp.first = p;
	p.x = -0.1720091644157867; p.y = 0.1782132876327338; hp.second = p;
	P1[2].push_back(hp);
	p.x = -0.1720091644157867; p.y = 0.1782132876327338; hp.first = p;
	p.x = -0.0985135050421326; p.y = -0.05734547389888543; hp.second = p;
	P1[2].push_back(hp);
	p.x = -0.0985135050421326; p.y = -0.05734547389888543; hp.first = p;
	p.x = 0.11677555947518725; p.y = -0.6430170331537365; hp.second = p;
	P1[2].push_back(hp);
	p.x = 0.11677555947518725; p.y = -0.6430170331537365; hp.first = p;
	p.x = 0.3174368333020072; p.y = -1.1690678061187554; hp.second = p;
	P1[2].push_back(hp);
	p.x = 0.3174368333020072; p.y = -1.1690678061187554; hp.first = p;
	p.x = 0.35134318956539234; p.y = -1.2536765122093974; hp.second = p;
	P1[2].push_back(hp);
	P2.push_back(std::vector<Halfplane>());
	p.x = 0.980842063577529; p.y = 0.36938415138749603; hp.first = p;
	p.x = 0.1679184856340561; p.y = 0.32239874999962825; hp.second = p;
	P2[2].push_back(hp);
	p.x = 0.1679184856340561; p.y = 0.32239874999962825; hp.first = p;
	p.x = 0.19137499008667302; p.y = 0.03689996730694611; hp.second = p;
	P2[2].push_back(hp);
	p.x = 0.19137499008667302; p.y = 0.03689996730694611; hp.first = p;
	p.x = 0.527524896201498; p.y = -0.17067602221405226; hp.second = p;
	P2[2].push_back(hp);
	p.x = 0.527524896201498; p.y = -0.17067602221405226; hp.first = p;
	p.x = 1.2296862933136223; p.y = -0.2997226047639342; hp.second = p;
	P2[2].push_back(hp);
	p.x = 1.2296862933136223; p.y = -0.2997226047639342; hp.first = p;
	p.x = 2.1061809446787416; p.y = -0.38269079791908045; hp.second = p;
	P2[2].push_back(hp);
	p.x = 2.1061809446787416; p.y = -0.38269079791908045; hp.first = p;
	p.x = 2.4643739891514054; p.y = -0.3831342945311064; hp.second = p;
	P2[2].push_back(hp);
	p.x = 2.4643739891514054; p.y = -0.3831342945311064; hp.first = p;
	p.x = 3.321761592950813; p.y = -0.3403040514514497; hp.second = p;
	P2[2].push_back(hp);
	p.x = 3.321761592950813; p.y = -0.3403040514514497; hp.first = p;
	p.x = 3.8575591506662557; p.y = -0.3117442030735216; hp.second = p;
	P2[2].push_back(hp);
	p.x = 3.8575591506662557; p.y = -0.3117442030735216; hp.first = p;
	p.x = 4.765026271014089; p.y = -0.2610584010049909; hp.second = p;
	P2[2].push_back(hp);
	p.x = 4.765026271014089; p.y = -0.2610584010049909; hp.first = p;
	p.x = 6.211894940928935; p.y = -0.17869621198811636; hp.second = p;
	P2[2].push_back(hp);
	P1.push_back(std::vector<Halfplane>());
	p.x = 0.16607338248877657; p.y = 0.03242423913236947; hp.first = p;
	p.x = 0.011247495428574728; p.y = 0.6750880140638181; hp.second = p;
	P1[3].push_back(hp);
	p.x = 0.011247495428574728; p.y = 0.6750880140638181; hp.first = p;
	p.x = 0.1096694672007521; p.y = 0.054314084661730266; hp.second = p;
	P1[3].push_back(hp);
	p.x = 0.1096694672007521; p.y = 0.054314084661730266; hp.first = p;
	p.x = 0.28791349365142205; p.y = -0.824844133612968; hp.second = p;
	P1[3].push_back(hp);
	p.x = 0.28791349365142205; p.y = -0.824844133612968; hp.first = p;
	p.x = 0.39209127955537976; p.y = -1.2969015617219102; hp.second = p;
	P1[3].push_back(hp);
	p.x = 0.39209127955537976; p.y = -1.2969015617219102; hp.first = p;
	p.x = 0.5492080288154373; p.y = -1.980174701159987; hp.second = p;
	P1[3].push_back(hp);
	p.x = 0.5492080288154373; p.y = -1.980174701159987; hp.first = p;
	p.x = 0.687958286686812; p.y = -2.573871368627447; hp.second = p;
	P1[3].push_back(hp);
	p.x = 0.687958286686812; p.y = -2.573871368627447; hp.first = p;
	p.x = 0.8939769454796601; p.y = -3.4428226836096174; hp.second = p;
	P1[3].push_back(hp);
	p.x = 0.8939769454796601; p.y = -3.4428226836096174; hp.first = p;
	p.x = 1.1181568366521395; p.y = -4.383053614069628; hp.second = p;
	P1[3].push_back(hp);
	p.x = 1.1181568366521395; p.y = -4.383053614069628; hp.first = p;
	p.x = 1.1679502521409992; p.y = -4.589936669693437; hp.second = p;
	P1[3].push_back(hp);
	p.x = 1.1679502521409992; p.y = -4.589936669693437; hp.first = p;
	p.x = 1.351168125406726; p.y = -5.350580877735258; hp.second = p;
	P1[3].push_back(hp);
	P2.push_back(std::vector<Halfplane>());
	p.x = 0.3809721868685648; p.y = 0.5661498137397012; hp.first = p;
	p.x = 0.2102127501804001; p.y = 0.36523993570078694; hp.second = p;
	P2[3].push_back(hp);
	p.x = 0.2102127501804001; p.y = 0.36523993570078694; hp.first = p;
	p.x = 0.7037024827332568; p.y = 0.7226446099020414; hp.second = p;
	P2[3].push_back(hp);
	p.x = 0.7037024827332568; p.y = 0.7226446099020414; hp.first = p;
	p.x = 0.9785662748835273; p.y = 0.9222919544839204; hp.second = p;
	P2[3].push_back(hp);
	p.x = 0.9785662748835273; p.y = 0.9222919544839204; hp.first = p;
	p.x = 1.258576917289715; p.y = 1.1732992518420684; hp.second = p;
	P2[3].push_back(hp);
	p.x = 1.258576917289715; p.y = 1.1732992518420684; hp.first = p;
	p.x = 1.3372738835024622; p.y = 1.2499320206122704; hp.second = p;
	P2[3].push_back(hp);
	p.x = 1.3372738835024622; p.y = 1.2499320206122704; hp.first = p;
	p.x = 1.4643684128979442; p.y = 1.397054034719143; hp.second = p;
	P2[3].push_back(hp);
	p.x = 1.4643684128979442; p.y = 1.397054034719143; hp.first = p;
	p.x = 1.5843392618171344; p.y = 1.5374192319104087; hp.second = p;
	P2[3].push_back(hp);
	p.x = 1.5843392618171344; p.y = 1.5374192319104087; hp.first = p;
	p.x = 1.6941607128008511; p.y = 1.6664845628417024; hp.second = p;
	P2[3].push_back(hp);
	p.x = 1.6941607128008511; p.y = 1.6664845628417024; hp.first = p;
	p.x = 1.8981537878843742; p.y = 1.9063924500037797; hp.second = p;
	P2[3].push_back(hp);
	p.x = 1.8981537878843742; p.y = 1.9063924500037797; hp.first = p;
	p.x = 2.014378443634704; p.y = 2.0431315623228894; hp.second = p;
	P2[3].push_back(hp);
	P1.push_back(std::vector<Halfplane>());
	p.x = 0.6750575785915148; p.y = 0.45611953832763297; hp.first = p;
	p.x = 0.00799487942844268; p.y = 0.36857615656381393; hp.second = p;
	P1[4].push_back(hp);
	p.x = 0.00799487942844268; p.y = 0.36857615656381393; hp.first = p;
	p.x = 0.2091478574521014; p.y = 0.11748041307133084; hp.second = p;
	P1[4].push_back(hp);
	p.x = 0.2091478574521014; p.y = 0.11748041307133084; hp.first = p;
	p.x = 0.4482088564117577; p.y = -0.0626389407414489; hp.second = p;
	P1[4].push_back(hp);
	p.x = 0.4482088564117577; p.y = -0.0626389407414489; hp.first = p;
	p.x = 1.1099745628657263; p.y = -0.09193555079470653; hp.second = p;
	P1[4].push_back(hp);
	p.x = 1.1099745628657263; p.y = -0.09193555079470653; hp.first = p;
	p.x = 1.4285208658603332; p.y = -0.07724577396101555; hp.second = p;
	P1[4].push_back(hp);
	p.x = 1.4285208658603332; p.y = -0.07724577396101555; hp.first = p;
	p.x = 2.1133726131387216; p.y = 0.003927384592596842; hp.second = p;
	P1[4].push_back(hp);
	p.x = 2.1133726131387216; p.y = 0.003927384592596842; hp.first = p;
	p.x = 2.8353348804664846; p.y = 0.09275327119786644; hp.second = p;
	P1[4].push_back(hp);
	p.x = 2.8353348804664846; p.y = 0.09275327119786644; hp.first = p;
	p.x = 3.7250018336352446; p.y = 0.20476010941234976; hp.second = p;
	P1[4].push_back(hp);
	p.x = 3.7250018336352446; p.y = 0.20476010941234976; hp.first = p;
	p.x = 4.550141169742426; p.y = 0.30952730989216315; hp.second = p;
	P1[4].push_back(hp);
	p.x = 4.550141169742426; p.y = 0.30952730989216315; hp.first = p;
	p.x = 5.098274437287522; p.y = 0.3813454974281337; hp.second = p;
	P1[4].push_back(hp);
	P2.push_back(std::vector<Halfplane>());
	p.x = 0.24786005964652036; p.y = 0.15351199666590187; hp.first = p;
	p.x = 0.8766442231727661; p.y = 0.32045832389358986; hp.second = p;
	P2[4].push_back(hp);
	p.x = 0.8766442231727661; p.y = 0.32045832389358986; hp.first = p;
	p.x = 0.019311824791733878; p.y = 0.7872473988145657; hp.second = p;
	P2[4].push_back(hp);
	p.x = 0.019311824791733878; p.y = 0.7872473988145657; hp.first = p;
	p.x = -0.5461202418634217; p.y = 0.8663621072041654; hp.second = p;
	P2[4].push_back(hp);
	p.x = -0.5461202418634217; p.y = 0.8663621072041654; hp.first = p;
	p.x = -1.511618094119624; p.y = 0.7528045288842464; hp.second = p;
	P2[4].push_back(hp);
	p.x = -1.511618094119624; p.y = 0.7528045288842464; hp.first = p;
	p.x = -2.481722529912182; p.y = 0.5928317179587508; hp.second = p;
	P2[4].push_back(hp);
	p.x = -2.481722529912182; p.y = 0.5928317179587508; hp.first = p;
	p.x = -2.630781251647858; p.y = 0.5547272410606945; hp.second = p;
	P2[4].push_back(hp);
	p.x = -2.630781251647858; p.y = 0.5547272410606945; hp.first = p;
	p.x = -2.8349045629973206; p.y = 0.5006500260475273; hp.second = p;
	P2[4].push_back(hp);
	p.x = -2.8349045629973206; p.y = 0.5006500260475273; hp.first = p;
	p.x = -2.9831277649002383; p.y = 0.4613167056083712; hp.second = p;
	P2[4].push_back(hp);
	p.x = -2.9831277649002383; p.y = 0.4613167056083712; hp.first = p;
	p.x = -3.6981930202521758; p.y = 0.2714770922016786; hp.second = p;
	P2[4].push_back(hp);
	p.x = -3.6981930202521758; p.y = 0.2714770922016786; hp.first = p;
	p.x = -4.140351106693518; p.y = 0.15408873990264915; hp.second = p;
	P2[4].push_back(hp);
	P1.push_back(std::vector<Halfplane>());
	p.x = 0.7601266021861098; p.y = 0.9579469156185711; hp.first = p;
	p.x = 0.9696118823752791; p.y = 0.0562823885965299; hp.second = p;
	P1[5].push_back(hp);
	p.x = 0.9696118823752791; p.y = 0.0562823885965299; hp.first = p;
	p.x = 0.9417707337476672; p.y = 0.9577204099225781; hp.second = p;
	P1[5].push_back(hp);
	p.x = 0.9417707337476672; p.y = 0.9577204099225781; hp.first = p;
	p.x = 0.8443372514258279; p.y = 1.4248265351539342; hp.second = p;
	P1[5].push_back(hp);
	p.x = 0.8443372514258279; p.y = 1.4248265351539342; hp.first = p;
	p.x = 0.7958691244632562; p.y = 1.6525120533153184; hp.second = p;
	P1[5].push_back(hp);
	p.x = 0.7958691244632562; p.y = 1.6525120533153184; hp.first = p;
	p.x = 0.7661199774287665; p.y = 1.7874796609912005; hp.second = p;
	P1[5].push_back(hp);
	p.x = 0.7661199774287665; p.y = 1.7874796609912005; hp.first = p;
	p.x = 0.6654679412745795; p.y = 2.221979800688329; hp.second = p;
	P1[5].push_back(hp);
	p.x = 0.6654679412745795; p.y = 2.221979800688329; hp.first = p;
	p.x = 0.4154476466913791; p.y = 3.2988458501085227; hp.second = p;
	P1[5].push_back(hp);
	p.x = 0.4154476466913791; p.y = 3.2988458501085227; hp.first = p;
	p.x = 0.06025241397944406; p.y = 4.828382123957746; hp.second = p;
	P1[5].push_back(hp);
	p.x = 0.06025241397944406; p.y = 4.828382123957746; hp.first = p;
	p.x = -0.003211873689972472; p.y = 5.101608064104535; hp.second = p;
	P1[5].push_back(hp);
	p.x = -0.003211873689972472; p.y = 5.101608064104535; hp.first = p;
	p.x = -0.2323356619630182; p.y = 6.087849891248453; hp.second = p;
	P1[5].push_back(hp);
	P2.push_back(std::vector<Halfplane>());
	p.x = 0.5089800185205492; p.y = 0.20852379842868707; hp.first = p;
	p.x = 0.8877587906602773; p.y = 0.9252408333382273; hp.second = p;
	P2[5].push_back(hp);
	p.x = 0.8877587906602773; p.y = 0.9252408333382273; hp.first = p;
	p.x = 0.21984765667897033; p.y = 0.40251614640840927; hp.second = p;
	P2[5].push_back(hp);
	p.x = 0.21984765667897033; p.y = 0.40251614640840927; hp.first = p;
	p.x = -0.07202148174076903; p.y = 0.07119916342693164; hp.second = p;
	P2[5].push_back(hp);
	p.x = -0.07202148174076903; p.y = 0.07119916342693164; hp.first = p;
	p.x = -0.24785230364537217; p.y = -0.1396546068898779; hp.second = p;
	P2[5].push_back(hp);
	p.x = -0.24785230364537217; p.y = -0.1396546068898779; hp.first = p;
	p.x = -0.7149505152298453; p.y = -0.9386846182071211; hp.second = p;
	P2[5].push_back(hp);
	p.x = -0.7149505152298453; p.y = -0.9386846182071211; hp.first = p;
	p.x = -1.2033833675165677; p.y = -1.838358786374477; hp.second = p;
	P2[5].push_back(hp);
	p.x = -1.2033833675165677; p.y = -1.838358786374477; hp.first = p;
	p.x = -1.5203946513813196; p.y = -2.433871487188544; hp.second = p;
	P2[5].push_back(hp);
	p.x = -1.5203946513813196; p.y = -2.433871487188544; hp.first = p;
	p.x = -1.8641194335456301; p.y = -3.082081823755338; hp.second = p;
	P2[5].push_back(hp);
	p.x = -1.8641194335456301; p.y = -3.082081823755338; hp.first = p;
	p.x = -2.2524004265620774; p.y = -3.8155001880278636; hp.second = p;
	P2[5].push_back(hp);
	p.x = -2.2524004265620774; p.y = -3.8155001880278636; hp.first = p;
	p.x = -2.752025715815427; p.y = -4.760053793686985; hp.second = p;
	P2[5].push_back(hp);
	P1.push_back(std::vector<Halfplane>());
	p.x = 0.6313140432511888; p.y = 0.4122617236748354; hp.first = p;
	p.x = 0.7604660031949979; p.y = 0.415031614348235; hp.second = p;
	P1[6].push_back(hp);
	p.x = 0.7604660031949979; p.y = 0.415031614348235; hp.first = p;
	p.x = 0.04751567903448384; p.y = 0.4736962378049121; hp.second = p;
	P1[6].push_back(hp);
	p.x = 0.04751567903448384; p.y = 0.4736962378049121; hp.first = p;
	p.x = -0.15061026125427057; p.y = 0.47956461324653354; hp.second = p;
	P1[6].push_back(hp);
	p.x = -0.15061026125427057; p.y = 0.47956461324653354; hp.first = p;
	p.x = -0.33239677373970544; p.y = 0.4835553064259722; hp.second = p;
	P1[6].push_back(hp);
	p.x = -0.33239677373970544; p.y = 0.4835553064259722; hp.first = p;
	p.x = -0.5424238589912651; p.y = 0.4848432719443555; hp.second = p;
	P1[6].push_back(hp);
	p.x = -0.5424238589912651; p.y = 0.4848432719443555; hp.first = p;
	p.x = -0.6762594395359443; p.y = 0.48313217869316266; hp.second = p;
	P1[6].push_back(hp);
	p.x = -0.6762594395359443; p.y = 0.48313217869316266; hp.first = p;
	p.x = -0.7448468399477203; p.y = 0.4820395110960628; hp.second = p;
	P1[6].push_back(hp);
	p.x = -0.7448468399477203; p.y = 0.4820395110960628; hp.first = p;
	p.x = -0.8984930082346759; p.y = 0.4789173596369495; hp.second = p;
	P1[6].push_back(hp);
	p.x = -0.8984930082346759; p.y = 0.4789173596369495; hp.first = p;
	p.x = -1.1456609437948; p.y = 0.47377186425552853; hp.second = p;
	P1[6].push_back(hp);
	p.x = -1.1456609437948; p.y = 0.47377186425552853; hp.first = p;
	p.x = -1.2928080690140427; p.y = 0.4706841656627695; hp.second = p;
	P1[6].push_back(hp);
	P2.push_back(std::vector<Halfplane>());
	p.x = 0.9801694711910932; p.y = 0.3316088255547206; hp.first = p;
	p.x = 0.9572766242963007; p.y = 0.8577604086330891; hp.second = p;
	P2[6].push_back(hp);
	p.x = 0.9572766242963007; p.y = 0.8577604086330891; hp.first = p;
	p.x = 0.0751744010377009; p.y = 0.3342414999340886; hp.second = p;
	P2[6].push_back(hp);
	p.x = 0.0751744010377009; p.y = 0.3342414999340886; hp.first = p;
	p.x = -0.580984990581261; p.y = -0.43425464691363397; hp.second = p;
	P2[6].push_back(hp);
	p.x = -0.580984990581261; p.y = -0.43425464691363397; hp.first = p;
	p.x = -0.8439843488277606; p.y = -0.9946367691566438; hp.second = p;
	P2[6].push_back(hp);
	p.x = -0.8439843488277606; p.y = -0.9946367691566438; hp.first = p;
	p.x = -0.8392767488758126; p.y = -1.4467661002453223; hp.second = p;
	P2[6].push_back(hp);
	p.x = -0.8392767488758126; p.y = -1.4467661002453223; hp.first = p;
	p.x = -0.8355118536789947; p.y = -1.8000002991114858; hp.second = p;
	P2[6].push_back(hp);
	p.x = -0.8355118536789947; p.y = -1.8000002991114858; hp.first = p;
	p.x = -0.8296624170931951; p.y = -2.0134637426661066; hp.second = p;
	P2[6].push_back(hp);
	p.x = -0.8296624170931951; p.y = -2.0134637426661066; hp.first = p;
	p.x = -0.8079622637188227; p.y = -2.549817012971763; hp.second = p;
	P2[6].push_back(hp);
	p.x = -0.8079622637188227; p.y = -2.549817012971763; hp.first = p;
	p.x = -0.7926956601570829; p.y = -2.9097184563429983; hp.second = p;
	P2[6].push_back(hp);
	p.x = -0.7926956601570829; p.y = -2.9097184563429983; hp.first = p;
	p.x = -0.7839413723704965; p.y = -3.1124820495211787; hp.second = p;
	P2[6].push_back(hp);
	P1.push_back(std::vector<Halfplane>());
	p.x = 0.7691411946122438; p.y = 0.94067559332255; hp.first = p;
	p.x = 0.7904180976970472; p.y = 0.7222774295151136; hp.second = p;
	P1[7].push_back(hp);
	p.x = 0.7904180976970472; p.y = 0.7222774295151136; hp.first = p;
	p.x = 0.9310927164844822; p.y = 0.6966857325454915; hp.second = p;
	P1[7].push_back(hp);
	p.x = 0.9310927164844822; p.y = 0.6966857325454915; hp.first = p;
	p.x = 0.9315902635319371; p.y = 0.8457905547853455; hp.second = p;
	P1[7].push_back(hp);
	p.x = 0.9315902635319371; p.y = 0.8457905547853455; hp.first = p;
	p.x = 0.9154724402933164; p.y = 1.1336513114316207; hp.second = p;
	P1[7].push_back(hp);
	p.x = 0.9154724402933164; p.y = 1.1336513114316207; hp.first = p;
	p.x = 0.8979742128220737; p.y = 1.407504697729376; hp.second = p;
	P1[7].push_back(hp);
	p.x = 0.8979742128220737; p.y = 1.407504697729376; hp.first = p;
	p.x = 0.8720559193464096; p.y = 1.7668134522517325; hp.second = p;
	P1[7].push_back(hp);
	p.x = 0.8720559193464096; p.y = 1.7668134522517325; hp.first = p;
	p.x = 0.8482388306776025; p.y = 2.058372753059449; hp.second = p;
	P1[7].push_back(hp);
	p.x = 0.8482388306776025; p.y = 2.058372753059449; hp.first = p;
	p.x = 0.8295255563415036; p.y = 2.2760247853054985; hp.second = p;
	P1[7].push_back(hp);
	p.x = 0.8295255563415036; p.y = 2.2760247853054985; hp.first = p;
	p.x = 0.796802025662715; p.y = 2.636293517968458; hp.second = p;
	P1[7].push_back(hp);
	p.x = 0.796802025662715; p.y = 2.636293517968458; hp.first = p;
	p.x = 0.7496850151950487; p.y = 3.13993237338592; hp.second = p;
	P1[7].push_back(hp);
	P2.push_back(std::vector<Halfplane>());
	p.x = 0.13038833688085083; p.y = 0.2545944499172561; hp.first = p;
	p.x = 0.6263276216542976; p.y = 0.39732568017706915; hp.second = p;
	P2[7].push_back(hp);
	p.x = 0.6263276216542976; p.y = 0.39732568017706915; hp.first = p;
	p.x = 0.574384382527553; p.y = 0.8972332581264489; hp.second = p;
	P2[7].push_back(hp);
	p.x = 0.574384382527553; p.y = 0.8972332581264489; hp.first = p;
	p.x = 0.24891096332164406; p.y = 0.9214649109218298; hp.second = p;
	P2[7].push_back(hp);
	p.x = 0.24891096332164406; p.y = 0.9214649109218298; hp.first = p;
	p.x = -0.4976930019991328; p.y = 0.8163672305467508; hp.second = p;
	P2[7].push_back(hp);
	p.x = -0.4976930019991328; p.y = 0.8163672305467508; hp.first = p;
	p.x = -1.2284965503903738; p.y = 0.6864374465449334; hp.second = p;
	P2[7].push_back(hp);
	p.x = -1.2284965503903738; p.y = 0.6864374465449334; hp.first = p;
	p.x = -1.405284140874201; p.y = 0.6414133440087729; hp.second = p;
	P2[7].push_back(hp);
	p.x = -1.405284140874201; p.y = 0.6414133440087729; hp.first = p;
	p.x = -1.9387293446198117; p.y = 0.4895848061757456; hp.second = p;
	P2[7].push_back(hp);
	p.x = -1.9387293446198117; p.y = 0.4895848061757456; hp.first = p;
	p.x = -2.607040344481908; p.y = 0.29875441365538913; hp.second = p;
	P2[7].push_back(hp);
	p.x = -2.607040344481908; p.y = 0.29875441365538913; hp.first = p;
	p.x = -3.2638418038382464; p.y = 0.11100689491208512; hp.second = p;
	P2[7].push_back(hp);
	p.x = -3.2638418038382464; p.y = 0.11100689491208512; hp.first = p;
	p.x = -4.341028401431277; p.y = -0.19781962473515394; hp.second = p;
	P2[7].push_back(hp);
	P1.push_back(std::vector<Halfplane>());
	p.x = 0.7891187191481346; p.y = 0.5342249155854896; hp.first = p;
	p.x = 0.5697533334483552; p.y = 0.09310284130480695; hp.second = p;
	P1[8].push_back(hp);
	p.x = 0.5697533334483552; p.y = 0.09310284130480695; hp.first = p;
	p.x = 0.8601663630690648; p.y = 0.6658756173531312; hp.second = p;
	P1[8].push_back(hp);
	p.x = 0.8601663630690648; p.y = 0.6658756173531312; hp.first = p;
	p.x = 1.088858268655361; p.y = 1.122884660909825; hp.second = p;
	P1[8].push_back(hp);
	p.x = 1.088858268655361; p.y = 1.122884660909825; hp.first = p;
	p.x = 1.4114241922073976; p.y = 1.7700267562099583; hp.second = p;
	P1[8].push_back(hp);
	p.x = 1.4114241922073976; p.y = 1.7700267562099583; hp.first = p;
	p.x = 1.7403975581890547; p.y = 2.430540789523947; hp.second = p;
	P1[8].push_back(hp);
	p.x = 1.7403975581890547; p.y = 2.430540789523947; hp.first = p;
	p.x = 1.935750347448409; p.y = 2.8231689368020696; hp.second = p;
	P1[8].push_back(hp);
	p.x = 1.935750347448409; p.y = 2.8231689368020696; hp.first = p;
	p.x = 2.0257357572257524; p.y = 3.004066380073913; hp.second = p;
	P1[8].push_back(hp);
	p.x = 2.0257357572257524; p.y = 3.004066380073913; hp.first = p;
	p.x = 2.2854556201917458; p.y = 3.526298809117018; hp.second = p;
	P1[8].push_back(hp);
	p.x = 2.2854556201917458; p.y = 3.526298809117018; hp.first = p;
	p.x = 2.4813269045278674; p.y = 3.9201535188065186; hp.second = p;
	P1[8].push_back(hp);
	p.x = 2.4813269045278674; p.y = 3.9201535188065186; hp.first = p;
	p.x = 2.529849065837138; p.y = 4.01772651984729; hp.second = p;
	P1[8].push_back(hp);
	P2.push_back(std::vector<Halfplane>());
	p.x = 0.5049144536619679; p.y = 0.009011578612337257; hp.first = p;
	p.x = 0.5109368332336549; p.y = 0.6857142140079449; hp.second = p;
	P2[8].push_back(hp);
	p.x = 0.5109368332336549; p.y = 0.6857142140079449; hp.first = p;
	p.x = 0.28305997296998364; p.y = 0.550066241204237; hp.second = p;
	P2[8].push_back(hp);
	p.x = 0.28305997296998364; p.y = 0.550066241204237; hp.first = p;
	p.x = 0.17802017809699178; p.y = -0.0777034531437649; hp.second = p;
	P2[8].push_back(hp);
	p.x = 0.17802017809699178; p.y = -0.0777034531437649; hp.first = p;
	p.x = 0.14492790827787544; p.y = -0.6782797004753979; hp.second = p;
	P2[8].push_back(hp);
	p.x = 0.14492790827787544; p.y = -0.6782797004753979; hp.first = p;
	p.x = 0.13246904848936356; p.y = -1.1582398203266335; hp.second = p;
	P2[8].push_back(hp);
	p.x = 0.13246904848936356; p.y = -1.1582398203266335; hp.first = p;
	p.x = 0.12536549084011647; p.y = -1.677029869515908; hp.second = p;
	P2[8].push_back(hp);
	p.x = 0.12536549084011647; p.y = -1.677029869515908; hp.first = p;
	p.x = 0.12011877149656879; p.y = -2.174308881903924; hp.second = p;
	P2[8].push_back(hp);
	p.x = 0.12011877149656879; p.y = -2.174308881903924; hp.first = p;
	p.x = 0.11159970079515097; p.y = -3.069829822853431; hp.second = p;
	P2[8].push_back(hp);
	p.x = 0.11159970079515097; p.y = -3.069829822853431; hp.first = p;
	p.x = 0.10094150251925427; p.y = -4.225120517562138; hp.second = p;
	P2[8].push_back(hp);
	p.x = 0.10094150251925427; p.y = -4.225120517562138; hp.first = p;
	p.x = 0.09424281143627848; p.y = -4.960372068166528; hp.second = p;
	P2[8].push_back(hp);
	P1.push_back(std::vector<Halfplane>());
	p.x = 0.9022457458881447; p.y = 0.3786396374405073; hp.first = p;
	p.x = 0.6874838621090197; p.y = 0.9770480491915757; hp.second = p;
	P1[9].push_back(hp);
	p.x = 0.6874838621090197; p.y = 0.9770480491915757; hp.first = p;
	p.x = 0.46341233157764805; p.y = 0.6957992202082358; hp.second = p;
	P1[9].push_back(hp);
	p.x = 0.46341233157764805; p.y = 0.6957992202082358; hp.first = p;
	p.x = 0.6430420886756516; p.y = 0.13223925081930854; hp.second = p;
	P1[9].push_back(hp);
	p.x = 0.6430420886756516; p.y = 0.13223925081930854; hp.first = p;
	p.x = 0.8750317977313125; p.y = -0.5245133991560257; hp.second = p;
	P1[9].push_back(hp);
	p.x = 0.8750317977313125; p.y = -0.5245133991560257; hp.first = p;
	p.x = 1.0892157245432408; p.y = -1.1270630783760696; hp.second = p;
	P1[9].push_back(hp);
	p.x = 1.0892157245432408; p.y = -1.1270630783760696; hp.first = p;
	p.x = 1.1882492271734406; p.y = -1.4050413987613382; hp.second = p;
	P1[9].push_back(hp);
	p.x = 1.1882492271734406; p.y = -1.4050413987613382; hp.first = p;
	p.x = 1.4577709327811479; p.y = -2.15806386145727; hp.second = p;
	P1[9].push_back(hp);
	p.x = 1.4577709327811479; p.y = -2.15806386145727; hp.first = p;
	p.x = 1.79451347982515; p.y = -3.098241768135824; hp.second = p;
	P1[9].push_back(hp);
	p.x = 1.79451347982515; p.y = -3.098241768135824; hp.first = p;
	p.x = 1.9592318700821894; p.y = -3.5573362110267293; hp.second = p;
	P1[9].push_back(hp);
	p.x = 1.9592318700821894; p.y = -3.5573362110267293; hp.first = p;
	p.x = 2.014383692829304; p.y = -3.7110417107983724; hp.second = p;
	P1[9].push_back(hp);
	P2.push_back(std::vector<Halfplane>());
	p.x = 0.7551206421517909; p.y = 0.9281685702918764; hp.first = p;
	p.x = 0.7377926895177994; p.y = 0.9929798419539828; hp.second = p;
	P2[9].push_back(hp);
	p.x = 0.7377926895177994; p.y = 0.9929798419539828; hp.first = p;
	p.x = 0.3506720904418289; p.y = 0.4722065111769602; hp.second = p;
	P2[9].push_back(hp);
	p.x = 0.3506720904418289; p.y = 0.4722065111769602; hp.first = p;
	p.x = 0.2984087142645572; p.y = 0.31957246739200884; hp.second = p;
	P2[9].push_back(hp);
	p.x = 0.2984087142645572; p.y = 0.31957246739200884; hp.first = p;
	p.x = 0.27691957855728605; p.y = 0.25085907962841686; hp.second = p;
	P2[9].push_back(hp);
	p.x = 0.27691957855728605; p.y = 0.25085907962841686; hp.first = p;
	p.x = 0.260611513742333; p.y = 0.18792179745157536; hp.second = p;
	P2[9].push_back(hp);
	p.x = 0.260611513742333; p.y = 0.18792179745157536; hp.first = p;
	p.x = 0.25413831908927104; p.y = 0.15248844122666091; hp.second = p;
	P2[9].push_back(hp);
	p.x = 0.25413831908927104; p.y = 0.15248844122666091; hp.first = p;
	p.x = 0.26451286007858266; p.y = 0.08026778540628929; hp.second = p;
	P2[9].push_back(hp);
	p.x = 0.26451286007858266; p.y = 0.08026778540628929; hp.first = p;
	p.x = 0.273909092098098; p.y = 0.03757809750955102; hp.second = p;
	P2[9].push_back(hp);
	p.x = 0.273909092098098; p.y = 0.03757809750955102; hp.first = p;
	p.x = 0.28584232429017264; p.y = -0.010309978562632764; hp.second = p;
	P2[9].push_back(hp);
	p.x = 0.28584232429017264; p.y = -0.010309978562632764; hp.first = p;
	p.x = 0.29785847443647173; p.y = -0.056866806657731445; hp.second = p;
	P2[9].push_back(hp);
}

void test() {
	UnboundedConvexPolygonIntersectionConstruction UCPIC;
	std::vector<std::vector<Halfplane>> P1, P2;
	generateUnboundedConvexPolygon(P1, P2);
	for (int i = 0; i < P1.size(); i++) {
		std::vector<std::vector<Halfplane>> P;
		P.push_back(UCPIC.bruteForce(P1[i], P2[i]));
		P.push_back(UCPIC.planeSweeping(P1[i], P2[i]));
		if (!isSame(P)) {
			std::cout << i << std::endl;
			std::cout << "P1 = " << std::endl;
			print(P1[i]);
			std::cout << "P2 = " << std::endl;
			print(P2[i]);
			std::cout << "bruteForce = " << std::endl;
			print(P[0]);
			std::cout << "planeSweeping = " << std::endl;
			print(P[1]);
			std::cin.get();
		}
	}
}

int main() {
	test();
	return 0;
}
