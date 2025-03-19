library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity task4 is
    Port ( CLK : in STD_LOGIC;
           RST : in STD_LOGIC;
           LED : out STD_LOGIC_VECTOR(0 to 2));
end task4;

architecture Behavioral of task4 is
        component task3_LFSR_out
            Generic(N: integer := 3;
                    init_state : std_logic_vector := "111");
            Port ( CLK : in STD_LOGIC;
                   RST : in STD_LOGIC;
                   Pout : out STD_LOGIC_VECTOR(0 to N-1));
         end component;
         
         component Frequency_Divider
            Port(
            CLK, RST: in std_logic;
            CLK_OUT: out std_logic);
         end component;

signal clk_small: std_logic;

begin
    Freq: Frequency_Divider port map(CLK => CLK, RST => RST, CLK_OUT => clk_small);
    LFSR: task3_LFSR_out port map(CLK => clk_small, RST => RST, Pout => LED);

end Behavioral;
