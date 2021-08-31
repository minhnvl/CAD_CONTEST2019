
    #include <bits/stdc++.h>
    #include <map>
    #include <regex>
    #include<string.h> 
    #include <iostream> 
    // #include "Code_ReadInput.h"
    using namespace std;

class condi
    {
        public:
        int maxlay;
        int maxcell; 
        int totalcell;
        vector <string> condicell; 
        vector <int> ggridbound;
        string   minrouting;
    };
class cell
    {
        public:
        vector <int>     numofpin;
        vector <string> mastercell;
    };
class net
    {
        public:
        vector <string> masternet;
        vector <string> routing;
        vector <string> result;
        int totalnetresult;
        
    };
    map <string, condi> Dict_Condition;
    map <string, cell> Dict_Cell;
    map < string, net> Dict_Net;

void Readfile(string path_input){
    cout << "**** Read File ****"  << endl;
    

    ifstream IFS_input;
    string line;
    string Namelabel;
    string dummy;
    string check_supply = "false";
    string check_mastercell = "false";
    string check_neighcell = "false";
    string check_numcell = "false";
    string check_netpin = "false";
    string check_netrouting =  "false";
    string value1,value2,value3;
   
    int value_maxcell;
    int colx,coly,rowx,rowy;
    int int1,int2,int3,int4,int5,int6;
    int count_check,total_check;
    
    regex find_Maxcellmove("MaxCellMove");
    regex find_GgridBound("GGridBoundaryIdx");
    regex find_maxlayer("NumLayer");
    regex find_Layer("^Lay");
    regex find_NonSupply("NumNonDefaultSupplyGGrid");
    regex find_NeighCell("NumNeighborCellExtraDemand");
    regex find_MasterCell("^MasterCell");
    regex find_Numcell("NumCellInst");
    regex find_Numnet("NumNets");
    regex find_NetPin("^Net");
    regex find_NetRouting("NumRoutes");
    regex find_elementRouting("\\d+ \\d+ \\d+ \\d+ \\d+ \\d+");
    regex find_Namenet("N\\d+");
    smatch match;
    


    // typedef std::map<const char*, int> BasePairMap;
    
    IFS_input.open(path_input.c_str());
    // BasePairMap Dict_Condition;
    
    while (getline(IFS_input,line)) {

        dummy.clear();
        istringstream token(line);
        if(regex_search(line,find_Maxcellmove)){
            token >> Namelabel >> value_maxcell;
            Dict_Condition["MaxCellMove"].maxcell = value_maxcell;
            // cout << Namelabel << " " << Dict_Condition["MaxCellMove"].maxcell << endl;
            // Max Cell Move 
        }
        else if (regex_search(line,find_GgridBound)){
            token >> Namelabel >> rowx >> colx >> rowy >> coly ;
            Dict_Condition["GGridBoundaryIdx"].ggridbound.push_back(rowx);
            Dict_Condition["GGridBoundaryIdx"].ggridbound.push_back(colx);
            Dict_Condition["GGridBoundaryIdx"].ggridbound.push_back(rowy);
            Dict_Condition["GGridBoundaryIdx"].ggridbound.push_back(coly);
            // cout << Namelabel << " "<<Dict_Condition["GGridBoundaryIdx"].ggridbound[3] << endl;
            
            // GgridBoundary colx rowx coly rowy
        } 
        else if(regex_search(line,find_maxlayer)){
            token >> dummy >> int1;
            Dict_Condition["NumLayer"].maxlay = int1;

        }
        else if (regex_search(line,find_Layer)) {
            token >> Namelabel >> value1 >> dummy >> value2 >> value3;
            string text = value2 + " " + value3; 
            Dict_Condition[value1.c_str()].condicell.push_back(text);
            // Dict_Condition[value1.c_str()].condicell.push_back(value3.c_str());
            // cout << Namelabel << " " << Dict_Condition[value1.c_str()].condicell[0]<< endl;
            // Layer in ggrid: Lay Namelay indx Dimension SupplyGgid
            // Lay M1 1 H 10
        }
        else if (regex_search(line,find_NonSupply)){
            token >> Namelabel >> total_check;
            count_check = 0;
            if (total_check == 0){
                Dict_Condition["NumNonDefaultSupplyGGrid"].condicell.push_back("False");
            }
            else {
                check_supply = "true";
            }
            continue;
            // cout << Namelabel << " " <<count_supply << endl;
        }
        else if (regex_search(line,find_NeighCell)){
            token >> dummy >> total_check;
            count_check = 0;
            if (total_check ==0){
                Dict_Condition["NumNeighborCellExtraDemand"].condicell.push_back("False");
            }
            else{
                check_neighcell = "true";
            }
            continue;
        }
        else if (regex_search(line,find_MasterCell)){
            token >> dummy >> Namelabel >> int1 >> int2;
            total_check = int1 + int2;
            Dict_Cell["NumofPin"].numofpin.push_back(int1); // Total of Pin in Master Cell
            count_check = 0;
            check_mastercell = "true";
            continue;
        }
        else if (regex_search(line,find_Numcell)){
            token >> dummy >> total_check;
            Dict_Condition["TotalCell"].totalcell = total_check; // Total of Cell in Circuit
            count_check = 0;
            check_numcell = "true";
            continue;
        }
        else if (regex_search(line,find_Numnet)){
            token >> dummy >> total_check;
            Dict_Condition["TotalNet"].totalcell = total_check;
            continue;

        }
        else if(regex_search(line,find_NetPin)){
            token >> dummy >> Namelabel >> total_check >> value1;
            Dict_Condition[Namelabel.c_str()].minrouting = value1;
            count_check = 0;
            check_netpin = "true";
            // cout << Dict_Condition[Namelabel.c_str()].minrouting << endl;
            continue;
        }
        else if (regex_search(line,find_NetRouting)){
            token >> dummy >> total_check;
            Dict_Net["Total"].totalnetresult = total_check;
            count_check = 0;
            check_netrouting = "true";
            continue;
        }
        
        // ######################################
        // Kiểm tra các điều kiện nhiều lần 
        if (check_supply == "true"){
            count_check++;
            Dict_Condition["NumNonDefaultSupplyGGrid"].condicell.push_back(line.c_str());
            // cout << Dict_Condition["NumNonDefaultSupplyGGrid"].condicell[count_check-1] << endl;

        } 
        else if (check_mastercell == "true"){
            // Namelabel.c_str() is MC1, MC2, MC3
            // Pin of master cell
            count_check++;
            token >> dummy >> value1 >> value2;
            line = line.substr(line.find(" ") + 1, line.length()) + " " + Dict_Condition[value2.c_str()].condicell[0];
            // cout << line << endl;
            Dict_Cell[Namelabel.c_str()].mastercell.push_back(line.c_str());
            // cout << Dict_Cell[Namelabel.c_str()].mastercell[count_check-1] << endl;
        }
        else if (check_neighcell == "true"){
            count_check++;
            Dict_Condition["NumNeighborCellExtraDemand"].condicell.push_back(line.c_str());
            // cout << Dict_Condition["NumNeighborCellExtraDemand"].condicell[count_check-1] << endl;

        }
        else if (check_numcell == "true"){
            count_check++;
            Dict_Cell["NumCellInst"].mastercell.push_back(line.c_str());
            // cout << Dict_Cell["NumCellInst"].mastercell[count_check-1] << endl;
        }
        else if (check_netpin == "true"){
            count_check++;
            token >> dummy >> value2;
            string namecell  = value2.substr(0, value2.find("/"));
            string indexpin   = value2.substr(value2.find("P") + 1,value2.length());

            string indexcell = namecell.substr(1,namecell.length());
            string mastercell = Dict_Cell["NumCellInst"].mastercell[stoi(indexcell)-1];
            // cout << mastercell << endl;
            istringstream token(mastercell);
            token >> dummy >> dummy >> value3 >> int1 >> int2 >> dummy;
            // cout << Dict_Cell[value3.c_str()].mastercell[stoi(indexpin)-1] << endl;
            value2 = value2 + " " + value3.c_str() + " " + to_string(int1) + " " + to_string(int2) + " " + Dict_Cell[value3.c_str()].mastercell[stoi(indexpin)-1];
            Dict_Net[Namelabel.c_str()].masternet.push_back(value2.c_str());
            Dict_Cell["CellofPin"].mastercell.push_back(namecell.c_str());
            // cout << Dict_Net[Namelabel.c_str()].masternet[count_check-1] << endl;
        }
        else if (check_netrouting == "true"){
            count_check++;
            // cout << count_check << endl;
            if (regex_search(line,match,find_elementRouting)){
                value2 = match.str();
            }
            if (regex_search(line,match,find_Namenet)){
                Namelabel = match.str();
            }
            Dict_Net[Namelabel.c_str()].routing.push_back(value2.c_str());
            // cout << Namelabel.c_str() << " " <<Dict_Net[Namelabel.c_str()].routing[count_check-1]<< endl;
        }

        // ###########################################

        if (count_check == total_check){
            check_supply = "false";
            check_mastercell = "false";
            check_neighcell = "false";
            check_numcell = "false";
            check_netpin = "false";
            check_netrouting = "false";
        }

    }
    // cout << Dict_Cell["NumCellInst"].mastercell[] << endl;

    IFS_input.close();
 
}


void PlacementCell(bool bool_case){
    cout << "Starting Placement" << endl;

    int Count_Cell,ValueX,ValueY;
    int ValueX_Same,ValueY_Same;
    int Sum_ZFT_X = 0;
    int Sum_ZFT_Y = 0;
    int Count_iter = 0;
    int Count_max = 0;
   
    string dummy;
    string Name_Cell,Value_Cell, Value_Layer, Check_movable;
    string Name_Cell_Same,Value_Cell_Same, Value_Layer_Same, Check_movable_Same;
   
    vector <int> Vector_WeightCell;
    map <string, int> Dict_WeightCell_Temp;

    // regex find_Cell("");
  
    // Tìm Giá trị Cell có weight lớn nhất  
    for( int i = 0; i < Dict_Condition["TotalCell"].totalcell; ++i)
    {
        Value_Cell = Dict_Cell["NumCellInst"].mastercell[i];
        istringstream token(Value_Cell);
        dummy.clear();

        token >> dummy >> Name_Cell >> Value_Layer >> ValueX >> ValueY >> Check_movable;
       
        if (Check_movable == "Movable"){
            // Tìm cell có trọng lượng lớn nhất 
            Count_Cell = count (Dict_Cell["CellofPin"].mastercell.begin(), Dict_Cell["CellofPin"].mastercell.end(), Name_Cell);
            Sum_ZFT_X = Sum_ZFT_X + ValueX*Count_Cell;
            Sum_ZFT_Y = Sum_ZFT_Y + ValueY*Count_Cell;
            Vector_WeightCell.push_back(Count_Cell); // Đếm Cell
        }
        else{
            Vector_WeightCell.push_back(0);
            continue;
        }
     
    }
    // Tính ZFT (Zero-Force-Target)

    //while (Count_iter < Dict_Condition["MaxCellMove"].maxcell + 3){
    while (Count_iter < 1 && bool_case == true){    
        ++Count_iter;
        // cout << "*****Placement with iteration " << Count_iter << " *****" << endl;
        int MaxCell = *max_element(Vector_WeightCell.begin(), Vector_WeightCell.end());;
        int PosmaxCell = distance(Vector_WeightCell.begin(), max_element(Vector_WeightCell.begin(), Vector_WeightCell.end()));
        int Sum_Weight = accumulate(Vector_WeightCell.begin(), Vector_WeightCell.end(),Count_max) - MaxCell;

        // Find the value ZFT, then subtrab with value of itself
        istringstream token(Dict_Cell["NumCellInst"].mastercell[PosmaxCell]);
        token >> dummy >> Name_Cell >> Value_Layer >> ValueX >> ValueY >> Check_movable;

        int Pos_X = round(float(Sum_ZFT_X - ValueX*MaxCell)/float(Sum_Weight));
        int Pos_Y = round(float(Sum_ZFT_Y - ValueY*MaxCell)/float(Sum_Weight));
        // CHeck Pos_X and Pos_Y living in GGrid
        if(Pos_X < Dict_Condition["GGridBoundaryIdx"].ggridbound[0] || Pos_X > Dict_Condition["GGridBoundaryIdx"].ggridbound[2] ){
            continue;
        }
        if(Pos_Y < Dict_Condition["GGridBoundaryIdx"].ggridbound[1] || Pos_Y > Dict_Condition["GGridBoundaryIdx"].ggridbound[3] ){
            continue;
        }
        // Check Position of ZFT exits
        string Selected_cell = " " + to_string(Pos_X) + " " + to_string(Pos_Y) + " ";
        regex find_POSZFT(Selected_cell);
        auto Check_Pos_Exits = find_if( Dict_Cell["NumCellInst"].mastercell.begin(), Dict_Cell["NumCellInst"].mastercell.end(), [&find_POSZFT](const string & word ){smatch m; return regex_search( word,m,find_POSZFT);});

        // Check the case ZFT location has CELL exits
        if (Check_Pos_Exits != Dict_Cell["NumCellInst"].mastercell.end()){ // If has Cell in ZFT location
            // cout << "Cell Exits: " << *Check_Pos_Exits << endl;
            int PosmaxCell_Same = distance(Dict_Cell["NumCellInst"].mastercell.begin(), Check_Pos_Exits);
            istringstream token(*Check_Pos_Exits);
            token >> dummy >> Name_Cell_Same >> Value_Layer_Same >> ValueX_Same >> ValueY_Same >> Check_movable_Same;
            string Save_cell_same = "CellInst " + Name_Cell_Same + " " +  Value_Layer_Same + " " + to_string(ValueX) + " " + to_string(ValueY) + " Movable";
            string Save_cell_Result1 = "CellInst " + Name_Cell_Same  + " " + to_string(ValueX) + " " + to_string(ValueY);
            
            if(Vector_WeightCell[PosmaxCell_Same] == 0){
                Vector_WeightCell[PosmaxCell_Same] = Dict_WeightCell_Temp["Pos" + Name_Cell_Same];
                // cout << "Poscellsame: " <<Dict_WeightCell_Temp["Pos" + Name_Cell_Same] << " " << PosmaxCell_Same << endl;
            }
            Count_max = Count_max - MaxCell;
            
            // Dict_Condition["MaxCellMove"].maxcell = Dict_Condition["MaxCellMove"].maxcell + 1;
           
            // Save reusult to export txt
            // string Save_cell_Result1 = "CellInst " + Name_Cell_Same  + " " + to_string(Pos_X) + " " + to_string(Pos_Y);
            regex find_cell_result1(" " + Name_Cell_Same + " ");
            regex find_exits_result1(Save_cell_same);
            
            auto Check_result_1 = find_if( Dict_Cell["ResultPlacement"].mastercell.begin(), Dict_Cell["ResultPlacement"].mastercell.end(), [&find_cell_result1](const string & word ){ return regex_search( word,find_cell_result1);});
            auto Check_exit_result_1 = find_if( Dict_Cell["NumCellInst"].mastercell.begin(), Dict_Cell["NumCellInst"].mastercell.end(), [&find_exits_result1](const string & word ){ return regex_search( word,find_exits_result1);});
            if(Check_exit_result_1 == Dict_Cell["NumCellInst"].mastercell.end()){
                if (Check_result_1 != Dict_Cell["ResultPlacement"].mastercell.end()){
                    // regex find_exits_result1(Save_cell_Result1);
                    
                    // auto Check_exit_result_1 = find_if( Dict_Cell["ResultPlacement"].mastercell.begin(), Dict_Cell["ResultPlacement"].mastercell.end(), [&find_exits_result1](const string & word ){ return regex_search( word,find_exits_result1);});
                    // // cout << Indx_result1 << endl;
                    // if(Check_exit_result_1 != Dict_Cell["ResultPlacement"].mastercell.end()){
                    //     int exit_result1 = distance(Dict_Cell["ResultPlacement"].mastercell.begin(), Check_exit_result_1);
                    //     // Dict_Cell["ResultPlacement"].mastercell.erase(exit_result1);
                    //     Dict_Cell["ResultPlacement"].mastercell.erase(Check_exit_result_1);
                    // }
                    // else{
                    //     int Indx_result1 = distance(Dict_Cell["ResultPlacement"].mastercell.begin(), Check_result_1);
                    //     Dict_Cell["ResultPlacement"].mastercell[Indx_result1] = Save_cell_Result1;
                    // }
                    int Indx_result1 = distance(Dict_Cell["ResultPlacement"].mastercell.begin(), Check_result_1);
                    Dict_Cell["ResultPlacement"].mastercell[Indx_result1] = Save_cell_Result1;
                    
                }
                else{
                    Dict_Cell["ResultPlacement"].mastercell.push_back(Save_cell_Result1);
                }
            }
            Dict_Cell["NumCellInst"].mastercell[PosmaxCell_Same] = Save_cell_same;
        
        }
        else { // If the Cell not exits
            // Lưu vị trí lại rồi tìm tiếp cell 
            // cout << "Cell Exits: None" << endl;
            Vector_WeightCell[PosmaxCell] = 0;
            Dict_WeightCell_Temp["Pos" + Name_Cell] = MaxCell;
            Count_max = Count_max + MaxCell;
        }
        
        string Save_cell = "CellInst " + Name_Cell + " " +  Value_Layer + Selected_cell + "Movable";
        string Save_cell_Result2 = "CellInst " + Name_Cell  + " " + to_string(Pos_X) + " " + to_string(Pos_Y);
        regex find_cell_result2(" " + Name_Cell + " ");
        regex find_exits_result2(Save_cell);
        

        // Save reusult to export txt
        auto Check_result_2 = find_if( Dict_Cell["ResultPlacement"].mastercell.begin(), Dict_Cell["ResultPlacement"].mastercell.end(), [&find_cell_result2](const string & word ){ return regex_search( word,find_cell_result2);});
        auto Check_exit_result_2 = find_if( Dict_Cell["NumCellInst"].mastercell.begin(), Dict_Cell["NumCellInst"].mastercell.end(), [&find_exits_result2](const string & word ){ return regex_search( word,find_exits_result2);});
        
        if(Check_exit_result_2 == Dict_Cell["NumCellInst"].mastercell.end()){
            if (Check_result_2 != Dict_Cell["ResultPlacement"].mastercell.end()){
                // regex find_exits_result2(Save_cell_Result2);
                // auto Check_exit_result_2 = find_if( Dict_Cell["ResultPlacement"].mastercell.begin(), Dict_Cell["ResultPlacement"].mastercell.end(), [&find_exits_result2](const string & word ){ return regex_search( word,find_exits_result2);});
                
                // if(Check_exit_result_2 != Dict_Cell["ResultPlacement"].mastercell.end()){
                //     int exit_result2 = distance(Dict_Cell["ResultPlacement"].mastercell.begin(), Check_exit_result_2);
                //     // Dict_Cell["ResultPlacement"].mastercell.erase(exit_result2);
                //     Dict_Cell["ResultPlacement"].mastercell.erase(Check_exit_result_2);
                // }
                // else{
                //     int Indx_result2 = distance(Dict_Cell["ResultPlacement"].mastercell.begin(), Check_result_2);
                //     Dict_Cell["ResultPlacement"].mastercell[Indx_result2] = Save_cell_Result2;  
                // }
                int Indx_result2 = distance(Dict_Cell["ResultPlacement"].mastercell.begin(), Check_result_2);
                Dict_Cell["ResultPlacement"].mastercell[Indx_result2] = Save_cell_Result2;  
            
            }
            else{
                Dict_Cell["ResultPlacement"].mastercell.push_back(Save_cell_Result2);
            }
        }
        //  Update result to file main dictionary
        Dict_Cell["NumCellInst"].mastercell[PosmaxCell] = Save_cell;
        
        
        
        // for_each (v.begin(), v.end(), [&re](const string & s) { v.push_back(s); } );
        // cout << "Max Cell Value: " << MaxCell << endl;
        // cout << "Pos Cell Value: " << PosmaxCell << endl;
        // cout << "Selected Weight: " << Name_Cell << endl;
        // cout << "Sum Weight: " << Sum_Weight << endl;
        // cout << "Sum ZFT X: " << Pos_X << endl;
        // cout << "Sum ZFT Y: " << Pos_Y << endl;

    }
    // cout << "************" << endl;
    // for (int z = 0; z < Dict_Cell["ResultPlacement"].mastercell.size(); ++z ){
    //     cout << Dict_Cell["ResultPlacement"].mastercell[z] << endl;
    // }
    // cout << "\nCells is changed in Placements: "<< endl;
    // for (int z = 0; z < Dict_Cell["NumCellInst"].mastercell.size(); ++z ){
    //     cout << Dict_Cell["NumCellInst"].mastercell[z] << endl;
    // }
}

void GlobalRouting(bool bool_case){
    cout << "Starting Routing" << endl;
    // For all net
    // for(int inet = 0; inet < )
    // string Name_select_Cell, Name_connect_Cell;
    string MC_select_Cell, MC_connect_Cell;
    string Pin_select, Pin_connect;
    string Dimension_select, Dimension_connect, tempdimension_select;
    string Demand_select, Demand_connect;
    string Layer_select, Layer_connect,Layer_consider, templayer_select;
    string result_1, result_2;
    string dummy;
    string x;
    int valrow_select, valcol_select;
    int valrow_connect, valcol_connect;
    int temrow_select, temcol_select;
    
    int Count_Result_net = 0;

    bool Bool_HVLayer = false;
    
    smatch match_cell_exits, match_cellofnet, match_cellmove;
    // cin >> x;
    dummy.clear();
    if( bool_case == true){
        for( int inet = 0; inet < Dict_Condition["TotalNet"].totalcell; ++inet){
            int X1_row, X1_col;
            string CellMove;
            bool bool_exit = false;
            bool bool_exit_HV = false;
            bool bool_move = false;
            // cout << "Processing Net N" << inet+1 << "..." << endl;
            // cout << "*******************" << endl;
            

            // Using fist pim to compare with others
            // Ussing the first element of cell to compare with others
            string NameNet = "N" + to_string(inet+1);

            // Phần thêm
            // Check net has movement cell
            for (int z = 0; z < Dict_Cell["ResultPlacement"].mastercell.size(); ++z ){
                istringstream tokencellmove(Dict_Cell["ResultPlacement"].mastercell[z]);
                tokencellmove >> dummy >> CellMove >> dummy >> dummy; 
                regex find_CellMove("^" + CellMove + "/" );
                // Check cell exit is cell of net
                auto Check_CellMove =  find_if( Dict_Net[NameNet.c_str()].masternet.begin(), Dict_Net[NameNet.c_str()].masternet.end(), [&find_CellMove,&match_cellmove](const string & word ){ return regex_search( word,match_cellmove,find_CellMove);});
                if(Check_CellMove != Dict_Net[NameNet.c_str()].masternet.end()){
                    break;
                }
                else{
                    bool_move = true;
                    for (int imove = 0; imove < Dict_Net[NameNet.c_str()].routing.size(); ++imove ){
                        string text2 = Dict_Net[NameNet.c_str()].routing[imove] + " " + NameNet.c_str();
                        Dict_Net[NameNet.c_str()].result.push_back(text2);
                    }   
                }
            }
                            




            for (int ipin = 0; ipin < Dict_Net[NameNet.c_str()].masternet.size(); ++ipin){
                if(bool_move == true){
                    break;
                }



                bool Stop = false;
                string Name_Cell = Dict_Net[NameNet.c_str()].masternet[ipin].substr(0,Dict_Net[NameNet.c_str()].masternet[ipin].find("/"));
                istringstream token_cell(Dict_Cell["NumCellInst"].mastercell[stoi(Name_Cell.substr(1,Name_Cell.length()))-1]);
                istringstream token_pin(Dict_Net[NameNet.c_str()].masternet[ipin]);

                if(ipin == 0){
                    // cout << "\nPin_Selected: " << Dict_Net[NameNet.c_str()].masternet[ipin] << endl;
                    // cout << "Cell_Selected: " << Dict_Cell["NumCellInst"].mastercell[stoi(Name_Cell.substr(1,Name_Cell.length()))-1] << endl;
                    token_cell >> dummy >> dummy >> dummy >> valrow_select >> valcol_select;
                    token_pin  >> dummy >> MC_select_Cell >> dummy >> dummy >> Pin_select >> Layer_select >> Dimension_select >> Demand_select;  
                    continue;
                }
                else{
                    // cout << "\nPin_Connected: " << Dict_Net[NameNet.c_str()].masternet[ipin] << endl;
                    // cout << "Cell_Connected: " << Dict_Cell["NumCellInst"].mastercell[stoi(Name_Cell.substr(1,Name_Cell.length()))-1] << endl;
                    token_cell >> dummy >> dummy >> dummy >> valrow_connect >> valcol_connect;
                    token_pin  >> dummy >> MC_connect_Cell >> dummy >> dummy >> Pin_connect >> Layer_connect >> Dimension_connect >> Demand_connect;  
                }


                temrow_select = valrow_select;
                temcol_select = valcol_select;
                templayer_select = Layer_select;
                tempdimension_select = Dimension_select;
                // Find the Temporary Denta Value to GlobalRouting
                while(Stop == false){
                    // cout << templayer_select << endl;
                    // cout << tempdimension_select << endl;
                    bool Check_DentaX_H = false;
                    bool Check_DentaX_V = false;
                    bool Check_minrouting = false;
                    bool Check_downlayer = false;
                    
                    string value_connect = " " + to_string(valrow_connect) + " " + to_string(valcol_connect) + " ";
                    int Num_Layer_Select = stoi(templayer_select.substr(1,templayer_select.length()));
                    int DentaX_H = abs(temrow_select - valrow_connect);
                    int DentaX_V = abs(temcol_select - valcol_connect);
                    int minlayer;
                    int signparam = 1;
                    // cout << "Net: " << NameNet.c_str() << endl;
                    // cout << "Coordinate Select:  " << temrow_select << " " << temcol_select << endl;
                    // cout << "Coordinate Connect:  " << valrow_connect << " " << valcol_connect << endl;
                    // cout << "DentaX_H: " << DentaX_H << " of " << temrow_select << " " << valcol_connect << endl;
                    // cout << "DentaX_V: " << DentaX_V << " of " << valrow_connect << " " << temcol_select << endl;
                    // cout << "Dimension Select: " << tempdimension_select << endl;
                    // Check the Minrouting of Net
                    if(Dict_Condition[NameNet.c_str()].minrouting != "NoCstr"){
                            // Check_minrouting = true;
                    

                        // cout << "Routing has minrouting" << endl;
                        minlayer = stoi(Dict_Condition[NameNet.c_str()].minrouting.substr(1,Dict_Condition[NameNet.c_str()].minrouting.length())) - 1;
                        if (Num_Layer_Select < stoi(Dict_Condition[NameNet.c_str()].minrouting.substr(1,Dict_Condition[NameNet.c_str()].minrouting.length()))){
                            // cout << 4444444444 << endl;
                            // cout << Num_Layer_Select << endl;
                            // cout << stoi(Dict_Condition[NameNet.c_str()].minrouting.substr(1,Dict_Condition[NameNet.c_str()].minrouting.length())) << endl;
                            // cout << "Numlayer smaller maxlayer" << endl;
                            Check_minrouting = true;
                            X1_row = temrow_select;
                            X1_col = temcol_select;
                
                        
                
                        }
                
                
                    }
                    else{
                        minlayer = 0;
                    }
                    
                    // Nếu như không có điều kiên min routing thì chạy bình thương
                    // X temporary 2 value (S_row,C_col) (C_row,S_col)
                    // Find coordinate for X
                    // **********************
                    if (Check_minrouting == false || bool_exit == true){ //08-04-2020 bool_exit
                        if(DentaX_H == DentaX_V){
                            if(tempdimension_select == "H"){
                                Check_DentaX_H = true;
                            }
                            else{
                                Check_DentaX_V = true;
                            }

                        }
                        else{
                            if (DentaX_H < DentaX_V){
                            
                            
                                if(tempdimension_select == "H"){
                                    Check_DentaX_H = true;
                                }
                                else{
                                    // cout << 33333333 << endl;
                                    tempdimension_select = "H";
                                    X1_row = temrow_select;
                                    X1_col = temcol_select;
                                }
                            
                            
                                // Check_DentaX_H = true;

                            }
                            else{
                                if(tempdimension_select == "V"){
                                    Check_DentaX_V = true;
                                }
                                else{
                                    // cout << 444444 << endl;
                                    tempdimension_select = "V";
                                    X1_row = temrow_select;
                                    X1_col = temcol_select;
                                }
                                // Check_DentaX_V = true;
                            }
                        }
                    }
        
                
                    if(Bool_HVLayer == true){
                        Check_DentaX_H = false;
                        Check_DentaX_V = false;
                        if(tempdimension_select == "H"){
                            Check_DentaX_H = true;
                        }
                        else{
                            Check_DentaX_V = true;
                        }
                    }
                    
                    // ************************ Edit 08/04 *********************
                    // Check layer meet exits Cell
                    // Layer tieep theo dieu chinh huong di chuyen
                    if(bool_exit == true){
                        int Tem_X1_row = X1_row;
                        int Tem_X1_col = X1_col;
                        int count_rout = 0;
                        int param_rout = 1;
                        bool stopexit = false;
                        while(stopexit == false){
                            // cout << "Meet Exits Cell and Change Layer, Routing in NewLayer" << endl;
                            ++count_rout;
                            // cout << Tem_X1_row << " " << Tem_X1_col << endl;
                            // cout << tempdimension_select << endl;
                            if(tempdimension_select == "V"){ // Nếu dimension hiện tại la H
                                //tempdimension_select = "V";
                                if(X1_col == Dict_Condition["GGridBoundaryIdx"].ggridbound[3]){
                                    Tem_X1_col = Tem_X1_col - 1;
                                }
                                else if(X1_col == Dict_Condition["GGridBoundaryIdx"].ggridbound[1]){
                                    Tem_X1_col = Tem_X1_col + 1;
                                }
                                else{
                                    if(count_rout%2 == 1){
                                        Tem_X1_col = Tem_X1_col + count_rout*param_rout;
                                    }
                                    else{
                                        Tem_X1_col = Tem_X1_col - count_rout*param_rout;
                                    }
                                }
                            }
                            
                            else{  // Nếu dimension hiện tại la V
                                //tempdimension_select = "H";
                                if(X1_row == Dict_Condition["GGridBoundaryIdx"].ggridbound[2]){
                                    Tem_X1_row = Tem_X1_row - 1;
                                }
                                else if(X1_row == Dict_Condition["GGridBoundaryIdx"].ggridbound[0]){
                                    Tem_X1_row = Tem_X1_row + 1;
                                }
                                else{
                                    if(count_rout%2 == 1){
                                        // cout << "aa" <<  Tem_X1_row << endl;
                                        Tem_X1_row = Tem_X1_row + count_rout*param_rout;
                                    }
                                    else{
                                        // cout << "bb" <<  Tem_X1_row << endl;
                                        // cout << count_rout<< "  "<<param_rout << endl;
                                        Tem_X1_row = Tem_X1_row - count_rout*param_rout;
                                    }
                                }
                            }
                            regex find_Cell_Exit(" " + to_string(Tem_X1_row) + " " + to_string(Tem_X1_col) + " ");
                            auto Check_Cell_Exits = find_if( Dict_Cell["NumCellInst"].mastercell.begin(), Dict_Cell["NumCellInst"].mastercell.end(), [&find_Cell_Exit](const string & word ){ return regex_search( word,find_Cell_Exit);});
                            if (Check_Cell_Exits != Dict_Cell["NumCellInst"].mastercell.end()){ // Exit cell when routing
                                param_rout = -1;
                            }
                            else{
                                X1_row = Tem_X1_row;
                                X1_col = Tem_X1_col;
                                stopexit = true;
                            }
                        }
                    }
                    // ****************************
                    
                    if (Check_DentaX_H == true){
                        X1_row = temrow_select;
                        X1_col = valcol_connect;
                
                        tempdimension_select = "V";
                        // Check sign to know up or down 
                        if (X1_col - temcol_select > 0){
                            signparam = 1;
                        }
                        else{
                            signparam = -1;
                        }
                        // cout << "Check value in Horizontal" << endl;
                        for (int icol=1; icol <= abs(temcol_select - X1_col); ++icol){
                            bool checkexit = false;
                            string Exits_Cell = " " + to_string(temrow_select) + " " + to_string(temcol_select + icol*signparam) + " ";
                            regex find_Cell(Exits_Cell);
                            // Check cell is element of Net
                
                            // Check cell exits is not element of Net
                            vector<string>::iterator it = Dict_Cell["NumCellInst"].mastercell.begin(); 
                            while((it = find_if( it, Dict_Cell["NumCellInst"].mastercell.end(), [&find_Cell,&match_cell_exits](const string & word ){ return regex_search( word,match_cell_exits,find_Cell);})) != Dict_Cell["NumCellInst"].mastercell.end())
                            {   
                                // Find index cell exit in routing
                                int Index_exits = distance(Dict_Cell["NumCellInst"].mastercell.begin(), it);
                                string valueexit;
                                istringstream token_Exits(Dict_Cell["NumCellInst"].mastercell[Index_exits]);
                                token_Exits >> dummy >> valueexit >> dummy >> dummy >> dummy >> dummy;
                                valueexit = "^" + valueexit + "/";
                                regex find_CellSameNet(valueexit);
                                // Check cell exit is cell of net
                                auto Check_CellofNet =  find_if( Dict_Net[NameNet.c_str()].masternet.begin(), Dict_Net[NameNet.c_str()].masternet.end(), [&find_CellSameNet,&match_cellofnet](const string & word ){ return regex_search( word,match_cellofnet,find_CellSameNet);});
                                // If cell of net X1_row is position of it
                                if (Check_CellofNet != Dict_Net[NameNet.c_str()].masternet.end()){ // If exits cell
                                    // cout << "Cell exits of net: " << Dict_Cell["NumCellInst"].mastercell[Index_exits] << endl;
                                    X1_col = temcol_select + icol*signparam;
                                    tempdimension_select = Dimension_connect;
                                    minlayer = 0;
                                    checkexit == true; // edit 08/04
                                    bool_exit = false; // edit 08/04
                                    break;
                                }
                                // If cell != net X1_row is before position
                                else{
                                    // cout << "Cell exits != net: " << Dict_Cell["NumCellInst"].mastercell[Index_exits] << endl;
                                    X1_col = temcol_select + icol*signparam - 1;
                                    bool_exit = true;
                                    // tempdimension_select = Dimension_connect;
                                    if(X1_col < 1){
                                        X1_col = temcol_select + icol*signparam + 1;
                                    }
                                    checkexit = true;
                                }
                                it++; 
                            }
                            if (checkexit == true){
                                break;
                            }
                            bool_exit = false;
                        }
                    }
                    else if(Check_DentaX_V == true){
                        X1_row = valrow_connect;
                        X1_col = temcol_select;
                    
                        tempdimension_select = "H";
                        // Check sign to know up or down 
                        if (X1_row - temrow_select > 0){
                            signparam = 1;
                        }
                        else{
                            signparam = -1;
                        }
                        // cout << "Check value in Vertical" << endl;
                        for (int irow=1; irow <= abs(temrow_select - X1_row); ++irow){
                            bool checkexit = false;
                            string Exits_Cell = " " + to_string(temrow_select + irow*signparam) + " " + to_string(temcol_select) + " ";
                            regex find_Cell(Exits_Cell);
                            // Check cell is element of Net
                    

                            // Check cell exits is not element of Net
                            vector<string>::iterator it = Dict_Cell["NumCellInst"].mastercell.begin(); 
                            while((it = find_if( it, Dict_Cell["NumCellInst"].mastercell.end(), [&find_Cell,&match_cell_exits](const string & word ){ return regex_search( word,match_cell_exits,find_Cell);})) != Dict_Cell["NumCellInst"].mastercell.end())
                            {   
                                // Find index cell exit in routing
                                int Index_exits = distance(Dict_Cell["NumCellInst"].mastercell.begin(), it);
                                string valueexit;
                                istringstream token_Exits(Dict_Cell["NumCellInst"].mastercell[Index_exits]);
                                token_Exits >> dummy >> valueexit >> dummy >> dummy >> dummy >> dummy;
                                valueexit = "^" + valueexit + "/";
                                regex find_CellSameNet(valueexit);
                                // Check cell exit is cell of net
                                auto Check_CellofNet =  find_if( Dict_Net[NameNet.c_str()].masternet.begin(), Dict_Net[NameNet.c_str()].masternet.end(), [&find_CellSameNet,&match_cellofnet](const string & word ){ return regex_search( word,match_cellofnet,find_CellSameNet);});
                                // If cell of net X1_row is position of it
                                if (Check_CellofNet != Dict_Net[NameNet.c_str()].masternet.end()){ // If exits cell
                                    // cout << "Cell exits of net: " << Dict_Cell["NumCellInst"].mastercell[Index_exits] << endl;
                                    X1_row = temrow_select + irow*signparam;
                                    tempdimension_select = Dimension_connect;
                                    minlayer = 0;
                                    checkexit == true; // edit 08/04
                                    bool_exit = false; // edit 08/04
                                    break;
                                }
                                // If cell != net X1_row is before position
                                else{
                                    // cout << "Cell exits != net: " << Dict_Cell["NumCellInst"].mastercell[Index_exits] << endl;
                                    bool_exit = true;
                                    X1_row = temrow_select + irow*signparam - 1;
                                    // tempdimension_select = Dimension_connect;
                                    if(X1_row < 1){
                                        X1_row = temrow_select + irow*signparam + 1;
                                    }
                                    
                                    checkexit = true;
                                }
                                it++; 
                    
                            }
                            if (checkexit == true){
                                break;
                            }
                            bool_exit = false;
                        }
                    }
                
                        
                    // cout << "X1_row: " << X1_row << endl;
                    // cout << "X1_col: " << X1_col << endl;
                    
                    // *****************

                    // Check layer 
                    // Kiểm tra số tâng phải đi lên
                    int denta_layer = Dict_Condition["NumLayer"].maxlay - Num_Layer_Select;
                    // int denta_layer_s = stoi(Layer_connect.substr(1,Layer_connect.length())) - Num_Layer_Select;
                    bool Check_layer = false;
                    int layer_up = 0;
                    int layer_down = 0;
                    int index_layer;
                    int count_check = 0;
                    // cout << denta_layer << endl;
                    // cout << Num_Layer_Select << endl;
                    // cout << "Current Layer: " << templayer_select << endl;
                    // cout << "Current Dimension: " << tempdimension_select << endl;
                    for(int ilay = minlayer; ilay < Dict_Condition["NumLayer"].maxlay; ++ilay){
                        if (denta_layer >= Num_Layer_Select){
                            // cout << "ok" << endl;
                            layer_up = layer_up + 1;
                            if(minlayer == 0){
                                index_layer = Num_Layer_Select + layer_up;
                            } 
                            // else if(Check_downlayer == true){
                            //     index_layer = Num_Layer_Select - layer_up;
                            // }   
                            else{
                                index_layer = minlayer + layer_up;
                            }
                            
                            
                        }
                        else{
                            // cout << "not ok" << endl;
                            layer_down = layer_down + 1;
                            index_layer = Num_Layer_Select - layer_down;
                        
                        }
                        if (index_layer < 1 ){
                            denta_layer = Num_Layer_Select;
                            if(ilay == denta_layer - 1){
                                Bool_HVLayer = true;
                            }
                            continue;
                        }
                        else if(index_layer > Dict_Condition["NumLayer"].maxlay){
                            denta_layer = Num_Layer_Select - 1;
                            if(ilay == denta_layer - 1){
                                Bool_HVLayer = true;
                            }
                            continue;
                        }
                        Layer_consider = "M" + to_string(index_layer);
                        // cout << Layer_consider << endl;
                        
                        string Dimension_consider = Dict_Condition[Layer_consider.c_str()].condicell[0].substr(0,1);
                        // cout << tempdimension_select << endl;
                        // cout << Dimension_consider << endl;
                        if (Dimension_consider == tempdimension_select){
                            Bool_HVLayer = false;
                            // cout << Bool_HVLayer << endl;
                            break;
                        }
                        else {
                            Layer_consider = templayer_select;
                            Bool_HVLayer = true;
                        }
                    }
                    if (Bool_HVLayer == true){
                        continue;
                    }
                
                    // cout << "Layer_consider: " << Layer_consider << endl;
                    

                    //**********************
                    // kiểm tra vị trí thay đổi có cùng vị trí hiện tại không
                    // Check position is changed or not changed
                    if(temrow_select == X1_row && temcol_select == X1_col){
                        // Nếu mà cùng thì lưu giá trị đi lên tầng tiếp theo
                        result_1  = "None" ;
                        result_2 = to_string(X1_row) + " " + to_string(X1_col) + " " + to_string(Num_Layer_Select) + " " + to_string(X1_row) + " " + to_string(X1_col) + " " +  Layer_consider.substr(1,Layer_consider.length()) + " " + NameNet.c_str();
                        // cout << result_1 << endl;
                        // cout << result_2 << endl;
                    }
                    else{
                        // Nếu không cùng thì lưu 2 giá trị
                        // 1 là giá trị đi lên tầng tiếp theo
                        // 2 là giá trị đi trong tầng
                        result_1 = to_string(temrow_select) + " " + to_string(temcol_select) + " " + to_string(Num_Layer_Select) + " " + to_string(X1_row) + " " + to_string(X1_col) + " " +  to_string(Num_Layer_Select) + " " + NameNet.c_str();
                        result_2 = to_string(X1_row) + " " + to_string(X1_col) + " " + to_string(Num_Layer_Select) + " " + to_string(X1_row) + " " + to_string(X1_col) + " " +  Layer_consider.substr(1,Layer_consider.length()) + " " + NameNet.c_str();
                        // cout << result_1 << endl;
                        // cout << result_2 << endl;
                    }
                    // cin >> x ;
                    // Save result in Dict
                    // Check result_1, result_2 exits in Dict_Result
                    regex find_result_2(result_2);
                    regex find_result_1(result_1);
                    // Check result_1 exits in Dict_Result
                    if(result_1 != "None"){
                        // Check result_1 exits in Dict_Result
                        auto Check_Net_Result_1 = find_if( Dict_Net[NameNet.c_str()].result.begin(), Dict_Net[NameNet.c_str()].result.end(), [&find_result_1](const string & word ){ return regex_search( word,find_result_1);});
                        if (Check_Net_Result_1 == Dict_Net[NameNet.c_str()].result.end()){
                            // Save result in Dict
                            Dict_Net[NameNet.c_str()].result.push_back(result_1);
                        }
                    }
                    // Check result_2 exits in Dict_Result
                    auto Check_Net_Result_2 = find_if( Dict_Net[NameNet.c_str()].result.begin(), Dict_Net[NameNet.c_str()].result.end(), [&find_result_2](const string & word ){ return regex_search( word,find_result_2);});
                    if (Check_Net_Result_2 == Dict_Net[NameNet.c_str()].result.end()){
                        // Save result in Dict
                        Dict_Net[NameNet.c_str()].result.push_back(result_2);
                    }

                    temrow_select = X1_row;
                    temcol_select = X1_col;
                    templayer_select  = Layer_consider;
                    if(temrow_select == valrow_connect && temcol_select == valcol_connect){
                        Stop = true;
                    }
                }
                
                // Take the remain value Cell to connect
                // string String_cell = Dict_Net[Namecell.c_str()].masternet[ipin].substr(1,Dict_Net[Namecell.c_str()].masternet[ipin].length() - 1);
                // string NumConnected_cell = String_cell.substr(0, String_cell.find("/"));
                // istringstream token(Dict_Cell["NumCellInst"].mastercell[stoi(NumConnected_cell)-1]);
                // token >> dummy >> Name_connect_Cell >> MC_connect_Cell >> valcol_connect >> valrow_connect;

                // // cout << NumConnected_cell << endl;
                // cout << Dict_Cell["NumCellInst"].mastercell[stoi(NumConnected_cell)-1] << endl;
                
                // Find The Direction of Pin



                // Find the Temporary Denta Value to GlobalRouting
                
                // int Denta1 = 

            }
            Count_Result_net = Count_Result_net + Dict_Net[NameNet.c_str()].result.size();
            Dict_Net["TotalNetResult"].totalnetresult = Count_Result_net;
            
            // cout << "**********Result************" << endl;
            // for(int icheck = 0; icheck < Dict_Net[NameNet.c_str()].result.size(); ++icheck){
            //     cout << Dict_Net[NameNet.c_str()].result[icheck] << endl; 
            // }

        }
    }
}

void SaveOutput(string path_output, bool bool_case){
    cout << "Starting Save Output" << endl;
    ofstream output_file(path_output);
    ostream_iterator<string> output_iterator(output_file, "\n");
    
    // Export Cell Movement
    output_file << "NumMovedCellInst " << Dict_Cell["ResultPlacement"].mastercell.size() << endl;
    copy(Dict_Cell["ResultPlacement"].mastercell.begin(), Dict_Cell["ResultPlacement"].mastercell.end(), output_iterator);
    
    // Export Routing of Net
    
    if (bool_case == true){
        output_file << "NumRoutes " << Dict_Net["TotalNetResult"].totalnetresult << endl;
        for (int inet = 0; inet < Dict_Condition["TotalNet"].totalcell; ++inet){
            string NameNet = "N" + to_string(inet+1);
            copy(Dict_Net[NameNet.c_str()].result.begin(), Dict_Net[NameNet.c_str()].result.end(), output_iterator);
        }
    }
    else{
        output_file << "NumRoutes " << Dict_Net["Total"].totalnetresult << endl;
        for (int inet = 0; inet < Dict_Condition["TotalNet"].totalcell; ++inet){
            string NameNet = "N" + to_string(inet+1);
            for (int result = 0;  result < Dict_Net[NameNet.c_str()].routing.size(); ++result){
                output_file << Dict_Net[NameNet.c_str()].routing[result] + " " + NameNet << endl;
            }
            
        }
    }
}

int main(int argc, char **argv) {
    
    string path_input = argv[1];
    string path_output = argv[2];
    bool   bool_case = false;
    regex find_case1("case1");
    regex find_case2("case2");
    cout << "**** Start ****" << endl;
    Readfile(path_input);
    if(regex_search(path_input,find_case1) || regex_search(path_input,find_case2)){
        bool_case = true;
    }
    PlacementCell(bool_case);
    GlobalRouting(bool_case);
    SaveOutput(path_output,bool_case);
    cout << "**** Done ****" << endl;

}
