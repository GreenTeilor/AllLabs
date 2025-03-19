library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity task2_beh is
    Generic(n : integer := 4);
    Port ( Sin : in STD_LOGIC;
           SE : in STD_LOGIC;
           CLK : in STD_LOGIC;
           RST : in STD_LOGIC;
           Dout : out STD_LOGIC_VECTOR(0 to n-1));
end task2_beh;

architecture Behavioral of task2_beh is
        signal register_state: std_logic_vector(0 to n-1);
begin
main: process (CLK, RST, Sin, SE)
    begin
      if RST = '1' then
            register_state <= (others => '0');
      elsif rising_edge(CLK) then
            if SE = '1' then
                register_state <= Sin & register_state(0 to n-2);
            end if;
      end if;
    end process; 
 Dout <= register_state;
end Behavioral;
