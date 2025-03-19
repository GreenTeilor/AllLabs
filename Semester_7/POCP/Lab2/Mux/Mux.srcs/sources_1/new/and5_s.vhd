library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity and5_s is
    Port (
    a : in STD_LOGIC_VECTOR(4 downto 0);
    z : out STD_LOGIC
);
end and5_s;

architecture a_and5_s of and5_s is
component and2 is
    port (
        a : in  STD_LOGIC;
        b : in  STD_LOGIC;
        z : out STD_LOGIC
    );
end component;
signal and2Outputs : STD_LOGIC_VECTOR(2 downto 0);
begin
   AND1: and2 port map (a => a(0), b => a(1), z => and2Outputs(0));
  
   gen_and: for i in 2 to 3 generate
       next_and: and2
           port map (
               a => and2Outputs(i-2),
               b => a(i),
               z => and2Outputs(i-1)
           );
   end generate;
   
   AND4: and2 port map (a => and2Outputs(2), b => a(4), z => z);
end a_and5_s;
