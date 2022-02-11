import json
import argparse
import numpy as np
import matplotlib.pyplot as plt
import random
from datetime import datetime
random.seed(datetime.now())

## assumptions:
## all points are listed in clockwise order.


# norlin_quad = [1096917, 396338, 1177401, 1337077, 1437282, 1397169, 1776796, 255849, 1656928,
#                 1876842, 1357122, 2076723, 35870, 1437281, 1137135, 856256, 1497069, 856255,
#                 1157312, 1316999, 1256757, 135927, 155908, 1377146, 1916620, 1796724, 1876841,
#                 1137138, 1497070, 896646, 456368, 996694, 1776795, 1357120, 536067, 155909,
#                 215847, 236028, 1096927, 876578, 16084, 35871, 436310, 336137, 916590, 1096918,
#                 715690]
# norlin_quad = [1776795, 536067]
# norlin_quad = [1617093]
norlin_quad = [1796724]

# 1 degree to meters. This is approx, and only works for things at 40 degree Lat (i.e., long_deg changes with the latitude)
lat_deg = 110950
long_deg = 85000

building_low = 0
building_high = 15

add_ground = True


def find_concave_convex(meter_v_array):
    cave_x = []
    vex_x = []
    cave_y = []
    vex_y = []

    num_v = len(meter_v_array)
    for j in range(num_v):
        A = meter_v_array[j]
        B = np.zeros(2)
        C = np.zeros(2)
        if j == 0:
            B = meter_v_array[j+1]
            C = meter_v_array[num_v-1]
        elif j == num_v - 1:
            B = meter_v_array[0]
            C = meter_v_array[j-1]
        else:
            B = meter_v_array[j+1]
            C = meter_v_array[j-1]

        opp = C[1] - A[1]
        adj = C[0] - A[0]
        hype = np.sqrt(opp*opp + adj*adj)
        c_cah = np.arccos(adj/hype)
        c_ans = c_cah
        if C[1] < A[1]:
            c_ans = np.pi + (np.pi-c_cah)
        opp = B[1] - A[1]
        adj = B[0] - A[0]
        hype = np.sqrt(opp*opp + adj*adj)
        b_cah = np.arccos(adj/hype)
        b_ans = b_cah
        if B[1] < A[1]:
            b_ans = np.pi + (np.pi-b_cah)

        ans = b_ans + (2*np.pi) - c_ans
        if ans > np.pi *2:
            ans = ans - np.pi*2
        if (ans > np.pi):
            vex_x.append(A[0])
            vex_y.append(A[1])
        else:
            cave_x.append(A[0])
            cave_y.append(A[1])
# need to add is there a point within the triangle test.
def cross2d(u, v):
    return u[1] * v[0] - u[0] * v[1]


## a list of the coordinates
## starting and ending point must be different
## [np.array([x,y]), np.array([x,y]), ...] must be of this form so that + - * opperations can be performed
def find_first_concave(meter_v_array):
    A = np.zeros(2)
    B = np.zeros(2)
    C = np.zeros(2)
    num_v = len(meter_v_array)
    # print("number of verticies is ", num_v)
    for j in range(num_v):
        A = meter_v_array[j]
        if j == 0:
            B = meter_v_array[j+1]
            C = meter_v_array[num_v-1]
        elif j == num_v - 1:
            B = meter_v_array[0]
            C = meter_v_array[j-1]
        else:
            B = meter_v_array[j+1]
            C = meter_v_array[j-1]

        # is A concave or convex
        opp = C[1] - A[1]
        adj = C[0] - A[0]
        hype = np.sqrt(opp*opp + adj*adj)
        # print("c_cah call {} {} {}".format(opp, adj, hype))
        # print("A {}, B {}, C {}".format(A, B, C))
        c_cah = np.arccos(adj/hype)
        c_ans = c_cah
        if C[1] < A[1]:
            c_ans = np.pi + (np.pi-c_cah)
        opp = B[1] - A[1]
        adj = B[0] - A[0]
        hype = np.sqrt(opp*opp + adj*adj)
        # print("b_cah call {} {} {}".format(opp, adj, hype))
        b_cah = np.arccos(adj/hype)
        b_ans = b_cah
        if B[1] < A[1]:
            b_ans = np.pi + (np.pi-b_cah)
        ans = b_ans + (2*np.pi) - c_ans
        if ans > np.pi*2: 
            ans = ans - np.pi*2
        if ans <= np.pi: ## if angle <= 180 degress, then it's concave
            ## A is concave
            # but, need to check if another point lays within the ABC triangle
            
            v_inside = False
            for k in range(num_v):
                if j == 0:
                    if k == j or k == j+1 or k == num_v-1:
                        continue
                elif j == num_v - 1:
                    if k == j or k == 0 or k == j-1:
                        continue
                else:
                    if k == j or k == j+1 or k == j-1:
                        continue
                # print(j,k)

                p_hit = meter_v_array[k]
                tester1 = cross2d(B - A, p_hit - A) # WARNING: ABC need to be clockwise
                tester2 = cross2d(C - B, p_hit - B)
                tester3 = cross2d(A - C, p_hit - C)
                # print("the testers are: ",tester1,tester2,tester3)
                if (tester1 > 0 and tester2 > 0) and tester3 > 0:
                    v_inside = True
                    break
            
            # return (np.array([A,B,C])) # returns the point and neighbors

            if v_inside == False:
                return j # returns the index of A


# parts are stuctured [[old], [new]]
# these are fixed buildings
# b202061i4 = [np.array([-104.93574202,   39.67378334]), np.array([-104.93574194,   39.6737407 ]), np.array([-104.93544919,   39.67385579]), np.array([-104.93546767,   39.67388618]), np.array([-104.93543458,   39.67389839]), np.array([-104.93547772,   39.67396569]), np.array([-104.93551107,   39.67394994]), np.array([-104.93547879,   39.67390558]), np.array([-104.93566112,   39.67383505]), np.array([-104.93570716,   39.6739115 ]), np.array([-104.9357438 ,   39.67389865]), np.array([-104.93578952,   39.67396806]), np.array([-104.93575372,   39.67398365]), np.array([-104.93576055,   39.67399248]), np.array([-104.93576617,   39.67399975]), np.array([-104.93581191,   39.67405894]), np.array([-104.93571923,   39.67409283]), np.array([-104.93574318,   39.67412775]), np.array([-104.93575677,   39.67414756]), np.array([-104.93576546,   39.67416022]), np.array([-104.93578126,   39.67418325]), np.array([-104.93571844,   39.6742108 ]), np.array([-104.93570079,   39.67418796]), np.array([-104.9355629 ,   39.67424228]), np.array([-104.93551576,   39.67416613]), np.array([-104.93547566,   39.67418998]), np.array([-104.93538324,   39.67422713]), np.array([-104.93534022,   39.67416447]), np.array([-104.93534658,   39.67416233]), np.array([-104.93534177,   39.67415508]), np.array([-104.93533795,   39.6741493 ]), np.array([-104.9353011 ,   39.67416352]), np.array([-104.9353011 ,   39.67416021]), np.array([-104.93525405,   39.67409406]), np.array([-104.9352908,   39.6740761]), np.array([-104.93528056,   39.67406387]), np.array([-104.93527478,   39.67406591]), np.array([-104.93523257,   39.67400271]), np.array([-104.93541221,   39.67393116]), np.array([-104.93540025,   39.67391153]), np.array([-104.93537044,   39.67392344]), np.array([-104.93534778,   39.67389076]), np.array([-104.93537943,   39.6738801 ]), np.array([-104.93535816,   39.67384654]), np.array([-104.93542643,   39.67382068]), np.array([-104.93542998,   39.67382068]), np.array([-104.93542999,   39.67382586]), np.array([-104.93574195,   39.67370152]), np.array([-104.93574183,   39.673634  ]), np.array([-104.93574182,   39.67362849]), np.array([-104.9357418 ,   39.67362253]), np.array([-104.9357417 ,   39.67356405]), np.array([-104.93574168,   39.67355678]), np.array([-104.93574167,   39.67355034]), np.array([-104.93574125,   39.6733214 ]), np.array([-104.93560321,   39.67332155]), np.array([-104.93560316,   39.67329546]), np.array([-104.93560315,   39.67328654]), np.array([-104.93560313,   39.67327975]), np.array([-104.93560239,   39.67287157]), np.array([-104.93545008,   39.67287173]), np.array([-104.93545016,   39.6729149 ]), np.array([-104.93532818,   39.67291503]), np.array([-104.9353281,   39.6728717]), np.array([-104.93511867,   39.67287193]), np.array([-104.93511872,   39.67289895]), np.array([-104.93511936,   39.67325011]), np.array([-104.93511937,   39.67325598]), np.array([-104.93511938,   39.67326088]), np.array([-104.93506382,   39.67326094]), np.array([-104.93506373,   39.67320948]), np.array([-104.93503398,   39.67320952]), np.array([-104.935034 ,   39.6732217]), np.array([-104.93501179,   39.67322172]), np.array([-104.93501181,   39.67323318]), np.array([-104.93495635,   39.67323324]), np.array([-104.93495633,   39.67322239]), np.array([-104.93493426,   39.67322242]), np.array([-104.93493422,   39.67320135]), np.array([-104.93485504,   39.67320144]), np.array([-104.93485499,   39.67317414]), np.array([-104.93485126,   39.67317414]), np.array([-104.93485123,   39.67315618]), np.array([-104.93483536,   39.67315619]), np.array([-104.93483529,   39.67311413]), np.array([-104.93484973,   39.67311412]), np.array([-104.93484967,   39.67308064]), np.array([-104.93483474,   39.67308065]), np.array([-104.93483466,   39.67303645]), np.array([-104.93485084,   39.67303644]), np.array([-104.93485078,   39.67300286]), np.array([-104.93483572,   39.67300288]), np.array([-104.93483564,   39.6729602 ]), np.array([-104.93485095,   39.67296018]), np.array([-104.93485092,   39.67294405]), np.array([-104.93485565,   39.67294405]), np.array([-104.93485564,   39.67293699]), np.array([-104.9348556 ,   39.67291463]), np.array([-104.93493613,   39.67291454]), np.array([-104.93493609,   39.67289462]), np.array([-104.93495564,   39.6728946 ]), np.array([-104.93495562,   39.67288252]), np.array([-104.93501236,   39.67288246]), np.array([-104.93501238,   39.67289482]), np.array([-104.93503341,   39.6728948 ]), np.array([-104.93503345,   39.67291618]), np.array([-104.93506271,   39.67291615]), np.array([-104.93506261,   39.67285967]), np.array([-104.93506259,   39.67285203]), np.array([-104.93506257,   39.67284008]), np.array([-104.93507668,   39.67284006]), np.array([-104.935244  ,   39.67283988]), np.array([-104.93530589,   39.67283981]), np.array([-104.93548338,   39.67283962]), np.array([-104.93548332,   39.6728071 ]), np.array([-104.93551973,   39.67280706]), np.array([-104.93551973,   39.6728072 ]), np.array([-104.93551976,   39.67282756]), np.array([-104.93565907,   39.67282741]), np.array([-104.93565921,   39.67290467]), np.array([-104.93568731,   39.67290464]), np.array([-104.93568729,   39.67289475]), np.array([-104.9357106 ,   39.67289473]), np.array([-104.93571057,   39.67288326]), np.array([-104.93576504,   39.67288321]), np.array([-104.93576506,   39.67289457]), np.array([-104.93586153,   39.67289447]), np.array([-104.93586162,   39.67294592]), np.array([-104.93589813,   39.67294589]), np.array([-104.93589824,   39.67300318]), np.array([-104.93587075,   39.67300321]), np.array([-104.93587081,   39.67303782]), np.array([-104.93588635,   39.6730378 ]), np.array([-104.93588643,   39.67308072]), np.array([-104.93586978,   39.67308074]), np.array([-104.93586984,   39.67311511]), np.array([-104.93588576,   39.6731151 ]), np.array([-104.93588583,   39.6731569 ]), np.array([-104.93587142,   39.67315692]), np.array([-104.93587145,   39.67317515]), np.array([-104.93586712,   39.67317515]), np.array([-104.93586717,   39.67320168]), np.array([-104.93578747,   39.67320177]), np.array([-104.93578751,   39.67322407]), np.array([-104.93568692,   39.67322418]), np.array([-104.93568687,   39.67320143]), np.array([-104.935658  ,   39.67320146]), np.array([-104.93565808,   39.67324469]), np.array([-104.93579958,   39.67324454]), np.array([-104.93579996,   39.67345509]), np.array([-104.93586876,   39.67345502]), np.array([-104.93586869,   39.67342024]), np.array([-104.93592792,   39.67342018]), np.array([-104.93592813,   39.67353664]), np.array([-104.93595564,   39.67353661]), np.array([-104.93595586,   39.67365646]), np.array([-104.93592888,   39.67365649]), np.array([-104.9359291 ,   39.67377597]), np.array([-104.93590044,   39.6737761 ]), np.array([-104.93590189,   39.67355157]), np.array([-104.93578609,   39.67355113]), np.array([-104.93578466,   39.67377382]), np.array([-104.9357846 ,   39.67378318]), np.array([-104.93577019,   39.67378323]), np.array([-104.93575959,   39.67378327]), np.array([-104.93574202,   39.67378334]), np.array([-104.93507383,   39.67309262]), np.array([-104.93507373,   39.67302388]), np.array([-104.93496602,   39.67302398]), np.array([-104.93496613,   39.67309272]), np.array([-104.93507383,   39.67309262])]    
# b202061i4_parts = [[0,169],[0, 166]] 
# b278432i1 = [np.array([-104.99333417,   39.71209616]), np.array([-104.993273  ,   39.71209568]), np.array([-104.99327479,   39.71195965]), np.array([-104.99327816,   39.71195968]), np.array([-104.99327851,   39.71193285]), np.array([-104.9932463,   39.7119326]), np.array([-104.99315941,   39.71193192]), np.array([-104.99312503,   39.71193164]), np.array([-104.9931249 ,   39.71194205]), np.array([-104.99314825,   39.71194223]), np.array([-104.99314783,   39.71197399]), np.array([-104.99312377,   39.7119738 ]), np.array([-104.99312307,   39.71202698]), np.array([-104.99268321,   39.71202352]), np.array([-104.99268338,   39.71201092]), np.array([-104.99259072,   39.71201019]), np.array([-104.99259064,   39.71201556]), np.array([-104.99255254,   39.71201526]), np.array([-104.99255651,   39.71171429]), np.array([-104.9925688 ,   39.71171438]), np.array([-104.99256923,   39.71168179]), np.array([-104.99255474,   39.71168168]), np.array([-104.99255649,   39.71154953]), np.array([-104.99254729,   39.71154946]), np.array([-104.99254768,   39.71152025]), np.array([-104.99255155,   39.71152028]), np.array([-104.99255237,   39.71145813]), np.array([-104.99254991,   39.71145811]), np.array([-104.99255135,   39.71134905]), np.array([-104.99270224,   39.71135024]), np.array([-104.99270222,   39.71135186]), np.array([-104.9927856 ,   39.71135251]), np.array([-104.99278548,   39.71136202]), np.array([-104.99282301,   39.71136231]), np.array([-104.99282311,   39.71135486]), np.array([-104.99298528,   39.71135614]), np.array([-104.99298533,   39.71135174]), np.array([-104.99313255,   39.7113529 ]), np.array([-104.99313195,   39.7113987 ]), np.array([-104.99314868,   39.71139875]), np.array([-104.99314945,   39.71143236]), np.array([-104.9931315 ,   39.71143229]), np.array([-104.99312988,   39.71155582]), np.array([-104.99298332,   39.71155467]), np.array([-104.99298383,   39.71151546]), np.array([-104.99295208,   39.71151521]), np.array([-104.99295162,   39.71154949]), np.array([-104.99286588,   39.71154881]), np.array([-104.99286609,   39.71153284]), np.array([-104.9928425 ,   39.71153265]), np.array([-104.99279844,   39.71156747]), np.array([-104.99279822,   39.71158469]), np.array([-104.99280505,   39.71158474]), np.array([-104.99280423,   39.71164742]), np.array([-104.99284771,   39.71164776]), np.array([-104.99284676,   39.71171951]), np.array([-104.99280393,   39.71171917]), np.array([-104.99280307,   39.71178461]), np.array([-104.99279646,   39.71178456]), np.array([-104.99279627,   39.71179943]), np.array([-104.99284374,   39.71183655]), np.array([-104.99286351,   39.71183671]), np.array([-104.99286373,   39.71182047]), np.array([-104.99294936,   39.71182115]), np.array([-104.9929489,   39.711856 ]), np.array([-104.99299523,   39.71185636]), np.array([-104.9929958 ,   39.71181276]), np.array([-104.99307565,   39.71181339]), np.array([-104.99307548,   39.71182596]), np.array([-104.99312498,   39.71182634]), np.array([-104.99312408,   39.71189444]), np.array([-104.99315826,   39.7118947 ]), np.array([-104.99324548,   39.71189539]), np.array([-104.99328165,   39.71189568]), np.array([-104.99328214,   39.71185841]), np.array([-104.99327782,   39.71185838]), np.array([-104.99327867,   39.71179399]), np.array([-104.99328411,   39.71179403]), np.array([-104.99328675,   39.71159383]), np.array([-104.9932803 ,   39.71159378]), np.array([-104.99328068,   39.71156486]), np.array([-104.99327842,   39.71156484]), np.array([-104.99328019,   39.71143047]), np.array([-104.99343955,   39.71143173]), np.array([-104.99343946,   39.7114387 ]), np.array([-104.99423082,   39.71144493]), np.array([-104.99423086,   39.71144125]), np.array([-104.99440967,   39.71144266]), np.array([-104.99445403,   39.71152564]), np.array([-104.99444906,   39.7115256 ]), np.array([-104.99444903,   39.71152746]), np.array([-104.99446742,   39.7115894 ]), np.array([-104.99442254,   39.71160449]), np.array([-104.99444512,   39.71162554]), np.array([-104.99449164,   39.71161173]), np.array([-104.9946626 ,   39.71191817]), np.array([-104.99467556,   39.71194317]), np.array([-104.99466745,   39.71194471]), np.array([-104.9946557 ,   39.71193195]), np.array([-104.99464967,   39.7119319 ]), np.array([-104.99466488,   39.71195122]), np.array([-104.99465338,   39.71199737]), np.array([-104.99466933,   39.7119975 ]), np.array([-104.99466845,   39.71206422]), np.array([-104.9946734 ,   39.71206426]), np.array([-104.99467274,   39.71211441]), np.array([-104.99459274,   39.71211378]), np.array([-104.9945927 ,   39.71211677]), np.array([-104.99410701,   39.71211295]), np.array([-104.99410699,   39.7121147 ]), np.array([-104.99399057,   39.71211379]), np.array([-104.99392456,   39.71211327]), np.array([-104.99392469,   39.71210346]), np.array([-104.99389327,   39.71210322]), np.array([-104.9938931 ,   39.71211625]), np.array([-104.99386897,   39.71211606]), np.array([-104.99386901,   39.71211277]), np.array([-104.99387196,   39.71157459]), np.array([-104.99343219,   39.71157315]), np.array([-104.99342924,   39.71210932]), np.array([-104.99342918,   39.71211445]), np.array([-104.99337194,   39.712114  ]), np.array([-104.99337202,   39.71210787]), np.array([-104.99333402,   39.71210758]), np.array([-104.99333417,   39.71209616]), np.array([-104.99430712,   39.71179415]), np.array([-104.99421983,   39.71163189]), np.array([-104.99418648,   39.71163169]), np.array([-104.99418642,   39.71163795]), np.array([-104.99414683,   39.7116377 ]), np.array([-104.99414672,   39.7116485 ]), np.array([-104.99405705,   39.71164794]), np.array([-104.99405723,   39.71163107]), np.array([-104.99403519,   39.71163093]), np.array([-104.99398932,   39.71166494]), np.array([-104.99398913,   39.71168264]), np.array([-104.99400313,   39.71168273]), np.array([-104.99400283,   39.71171139]), np.array([-104.99401511,   39.71171146]), np.array([-104.99401363,   39.71185482]), np.array([-104.99399923,   39.71185473]), np.array([-104.99399894,   39.71188315]), np.array([-104.99398786,   39.71188308]), np.array([-104.99398769,   39.7119001 ]), np.array([-104.99403272,   39.71193476]), np.array([-104.99405415,   39.71193489]), np.array([-104.99405425,   39.71192479]), np.array([-104.99409086,   39.71192501]), np.array([-104.99409097,   39.71191447]), np.array([-104.99427648,   39.71191561]), np.array([-104.99427703,   39.7119262 ]), np.array([-104.99431376,   39.7119262 ]), np.array([-104.99431376,   39.71193763]), np.array([-104.99433514,   39.71193721]), np.array([-104.99438558,   39.71189233]), np.array([-104.99437791,   39.71187751]), np.array([-104.99435676,   39.71188462]), np.array([-104.99432299,   39.711823  ]), np.array([-104.9943315 ,   39.71182021]), np.array([-104.99431568,   39.71179134]), np.array([-104.99430712,   39.71179415])]
# b278432i1_parts = [[0,125],[0,125]] # no change because the removed points are in the last part


def main():
    parser = argparse.ArgumentParser(description="geojson dataset please")
    parser.add_argument("geojson_f", nargs="?")
    parser.add_argument("--output", nargs="?", default="new.obj")
    args = parser.parse_args()
    
    geojson_f = args.geojson_f
    # print(args.output)
    print("reading {} geojson file".format(geojson_f))

    # # Opening JSON file
    f = open(geojson_f)
    
    # # returns JSON object as
    # # a dictionary
    data = json.load(f)
    
    FIDs = []
    vertex_degrees = []
    # # Iterating through the json
    # # list
    for i in data['features']:
        if i["properties"]["FID"] in norlin_quad:
        # if True:
            # print(i["properties"]["FID"])
            FIDs.append(i["properties"]["FID"])
            # print(i["geometry"]["coordinates"][0][0])
            vertex_degrees.append(i["geometry"]["coordinates"][0][0])
    
    # # Closing file
    f.close()
    # # clear data from memory
    del data

    a_FIDs = np.array(FIDs)
    a_vertex_degrees = np.array(vertex_degrees, dtype=object)
    # print(a_vertex_degrees[0][0])
    lower_left = np.array([a_vertex_degrees[0][0][0], a_vertex_degrees[0][0][1]])
    upper_right = np.array([a_vertex_degrees[0][0][0], a_vertex_degrees[0][0][1]])
    points_to_average = 0
    # # find geographic center
    for i in range(len(a_vertex_degrees)):
        for j in range(len(a_vertex_degrees[i])):
            if a_vertex_degrees[i][j][0] < lower_left[0]:
                lower_left[0] = a_vertex_degrees[i][j][0]
            if a_vertex_degrees[i][j][0] > upper_right[0]:
                upper_right[0] = a_vertex_degrees[i][j][0]
            if a_vertex_degrees[i][j][1] < lower_left[1]:
                lower_left[1] = a_vertex_degrees[i][j][1]
            if a_vertex_degrees[i][j][1] > upper_right[1]:
                upper_right[1] = a_vertex_degrees[i][j][1]    
    print("lower left is {}".format(lower_left))
    print("upper right is {}".format(upper_right))

    geo_center = np.zeros(2)
    geo_center[0] = (lower_left[0] + upper_right[0]) / 2.0
    geo_center[1] = (lower_left[1] + upper_right[1]) / 2.0
    ## geo_center is still in long,lat
    # meter_geo_center = (geo_center - lower_left) * np.array([long_deg, lat_deg])

    bb_meters = np.zeros((2,2))
    bb_meters[1] = (upper_right - lower_left) *  np.array([long_deg, lat_deg])
    print(bb_meters)

    # vertex_count 
    vc = 0
    bc = 0
    # v_list = []
    # f_list = []

    # xx = []
    # yy = []
    ## outfile
    # f = open(args.output, 'w')
    # f.write("mtllib norlin.mtl\ng norlin_quad\n")
    for i in range(len(a_vertex_degrees)):
        xx = []
        yy = []
        sx_0 = 0.0
        sy_0 = 0.0
        sx_1 = 0.0
        sy_1 = 0.0
        meter_v_array = np.zeros((len(a_vertex_degrees[i])-1, 2))
        for j in range(0, len(a_vertex_degrees[i])):
            xx.append((a_vertex_degrees[i][j][0] - lower_left[0]) * long_deg)
            yy.append((a_vertex_degrees[i][j][1] - lower_left[1]) * lat_deg)
            if j == 0:
                sx_0 = (a_vertex_degrees[i][j][0] - lower_left[0]) * long_deg
                sy_0 = (a_vertex_degrees[i][j][1] - lower_left[1]) * lat_deg
            if j == 1:
                sx_1 = (a_vertex_degrees[i][j][0] - lower_left[0]) * long_deg
                sy_1 = (a_vertex_degrees[i][j][1] - lower_left[1]) * lat_deg
            if j != len(a_vertex_degrees[i])-1:
                meter_v_array[j] = (a_vertex_degrees[i][j] - lower_left) * np.array([long_deg, lat_deg])

        # plt.plot(xx,yy)
        # plt.scatter(sx_0,sy_0,color='r',s=45)
        # plt.scatter(sx_1,sy_1,color='b',s=45)
        # plt.show()    
        # print(meter_v_array)


        # find first concave
        v_list = []
        f_list = []
        ret = find_first_concave(meter_v_array)
        print(ret)
        f_list.append("f {} {} {}".format(vc-1, vc-building_vc+1, vc-building_vc+2))
        ## write triangle A,B,C out to file and remove A


    print("{} written out.\n{} is the geographic center.".format(args.output, (geo_center - lower_left) * np.array([long_deg, lat_deg])))










if __name__ == "__main__":
    main()

