library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity summator_1_s is
    Port ( x1 : in STD_LOGIC;
           x2 : in STD_LOGIC;
           x3 : in STD_LOGIC;
           y1 : out STD_LOGIC;
           y2 : out STD_LOGIC);
end summator_1_s;

architecture a_summator_1_s of summator_1_s is
component and3 is 
    port (
        a, b, c : in STD_LOGIC;
        z: out STD_LOGIC
    );
end component;
component or4 is 
    port (
        a, b, c, d : in STD_LOGIC;
        z: out STD_LOGIC
    );
end component;
component inv is
    port (
        a: in STD_LOGIC;
        z: out STD_LOGIC
    );
end component;
signal nx1, nx2, nx3: STD_LOGIC;
signal nnx, nxn, xnn, xxx: STD_LOGIC;
signal nxx, xnx, xxn: STD_LOGIC;
begin
    U1: inv port map (a => x1, z => nx1);
    U2: inv port map (a => x2, z => nx2);
    U3: inv port map (a => x3, z => nx3);
    
    NX1_NX2_X3: and3 port map (a => nx1, b => nx2, c => x3, z => nnx);
    NX1_X2_NX3: and3 port map (a => nx1, b => x2, c => nx3, z => nxn);  
    X1_NX2_NX3: and3 port map (a => x1, b => nx2, c => nx3, z => xnn);   
    X1_X2_X3: and3 port map (a => x1, b => x2, c => x3, z => xxx);
    
    NX1_X2_X3: and3 port map (a => nx1, b => x2, c => x3, z => nxx);
    X1_NX2_X3: and3 port map (a => x1, b => nx2, c => x3, z => xnx);
    X1_X2_NX3: and3 port map (a => x1, b => x2, c => nx3, z => xxn);
    
    OUT_Y1: or4 port map (a => nnx, b => nxn, c => xnn, d => xxx, z => y1);
    OUT_Y2: or4 port map (a => nxx, b => xnx, c => xxn, d => xxx, z => y2);            
end a_summator_1_s;