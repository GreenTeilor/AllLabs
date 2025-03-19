----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 15.09.2024 18:47:20
-- Design Name: 
-- Module Name: mux - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity mux is
    Port ( A : in STD_LOGIC;
           B : in STD_LOGIC;
           S : in STD_LOGIC;
           Z : out STD_LOGIC);
end mux;

architecture Behavioral of mux is

begin
    Z<=A when S='0' else B;
end Behavioral;
