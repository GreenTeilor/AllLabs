library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity task3_LFSR_In is
    Generic(n : integer := 3;
            init_state : std_logic_vector := "111";
            alpha : std_logic_vector := "0101");
    Port ( CLK : in STD_LOGIC;
           RST : in STD_LOGIC;
           Pout : out STD_LOGIC_VECTOR(alpha'high - 1 downto 0));
end task3_LFSR_In;

architecture Behavioral of task3_LFSR_In is
        signal register_state: std_logic_vector(alpha'high - 1 downto 0) := init_state;
        signal data_state: std_logic_vector(alpha'high - 1 downto 0) := init_state; 
       
Begin

Main: process(CLK, RST)
begin
if RST = '1' then
   register_state <= init_state;
  elsif rising_edge(CLK) then 
  register_state <= data_state;
  end if;
  end process;
    
Generation: process (register_state)
 variable zero_bit: std_logic := '0'; 
 variable new_bit: std_logic := '0';
 begin
    for i in alpha'high-1 downto 1 loop
        zero_bit := zero_bit or register_state(i);
        if alpha(i) = '1' then
            data_state(i) <= register_state(alpha'high - 1) xor register_state(i-1);
        else
        data_state(i) <= register_state(i-1);
        end if;
    end loop;
      zero_bit := not zero_bit; 
      data_state(0) <= register_state(alpha'high - 1) xor zero_bit;
 end process; 
 
 Pout <= register_state;


end Behavioral;