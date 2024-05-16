USE [exploration]

SET IDENTITY_INSERT [rooms] ON;
INSERT INTO [rooms] ([r_id], [r_name], [r_space])
VALUES
(1, N'������� � ����� ������������', 5),
(2, N'������� � ����� ������������', 5),
(3, N'������ ������� 1', 2),
(4, N'������ ������� 2', 2),
(5, N'������ ������� 3', 2);
SET IDENTITY_INSERT [rooms] OFF;

SET IDENTITY_INSERT [computers] ON;
INSERT INTO [computers] ([c_id], [c_room], [c_name])
VALUES
(1, 1, N'��������� A � ������� 1'),
(2, 1, N'��������� B � ������� 1'),
(3, 2, N'��������� A � ������� 2'),
(4, 2, N'��������� B � ������� 2'),
(5, 2, N'��������� C � ������� 2'),
(6, NULL, N'��������� ��������� A'),
(7, NULL, N'��������� ��������� B'),
(8, NULL, N'��������� ��������� C');
SET IDENTITY_INSERT [computers] OFF;

SET IDENTITY_INSERT [library_in_json] ON;
INSERT INTO [library_in_json]
(
    [lij_id],
	[lij_book],
    [lij_author],
    [lij_genre]
) VALUES
(1, N'������� ������', N'[{"id":7,"name":"�.�. ������"}]', N'[{"id":1,"name":"������"},{"id":5,"name":"��������"}]'),
(2, N'��������� ����������������', N'[{"id":1,"name":"�. ����"}]', N'[{"id":2,"name":"����������������"},{"id":5,"name":"��������"}]'),
(3, N'���� ������������� ������', N'[{"id":4,"name":"�.�. ������"},{"id":5,"name":"�.�. ������"}]', N'[{"id":5,"name":"��������"}]'),
(4, N'��������� � �������', N'[{"id":2,"name":"�. ������"}]', N'[{"id":6,"name":"����������"}]'),
(5, N'���������� ����������������', N'[{"id":3,"name":"�. �������"},{"id":6,"name":"�. ����������"}]', N'[{"id":2,"name":"����������������"},{"id":3,"name":"����������"}]'),
(6, N'������ � ������ � �����', N'[{"id":7,"name":"�.�. ������"}]', N'[{"id":1,"name":"������"},{"id":5,"name":"��������"}]'),
(7, N'���� ���������������� �++', N'[{"id":6,"name":"�. ����������"}]', N'[{"id":2,"name":"����������������"}]');
SET IDENTITY_INSERT [library_in_json] OFF;


SET IDENTITY_INSERT [site_pages] ON;
INSERT INTO [site_pages] ([sp_id], [sp_parent], [sp_name]) VALUES
(1, NULL, N'�������'),
(2, 1, N'���������'),
(3, 1, N'���������'),
(4, 1, N'��������������'),
(5, 2, N'�������'),
(6, 2, N'����������'),
(7, 3, N'�����������'),
(8, 3, N'������� ������'),
(9, 4, N'�����'),
(10, 1, N'��������'),
(11, 3, N'���������'),
(12, 6, N'�������'),
(13, 6, N'��������'),
(14, 6, N'�������������');
SET IDENTITY_INSERT [site_pages] OFF;

SET IDENTITY_INSERT [cities] ON;
INSERT INTO [cities] ([ct_id], [ct_name]) VALUES
(1, N'������'),
(2, N'�����'),
(3, N'������'),
(4, N'�����'),
(5, N'������'),
(6, N'����'),
(7, N'�����'),
(8, N'����'),
(9, N'�������'),
(10, N'������');
SET IDENTITY_INSERT [cities] OFF;

INSERT INTO [connections] ([cn_from], [cn_to], [cn_cost], [cn_bidir]) VALUES
(1, 5, 10, 'Y'),
(1, 7, 20, 'N'),
(7, 1, 25, 'N'),
(7, 2, 15, 'Y'),
(2, 6, 50, 'N'),
(6, 8, 40, 'Y'),
(8, 4, 30, 'N'),
(4, 8, 35, 'N'),
(8, 9, 15, 'Y'),
(9, 1, 20, 'N'),
(7, 3, 5, 'N'),
(3, 6, 5, 'N');

SET IDENTITY_INSERT [shopping] ON;
INSERT INTO [shopping]
(
    [sh_id],
    [sh_transaction],
    [sh_category]
) VALUES
(1, 1, N'�����'),
(2, 1, N'������'),
(3, 1, N'�����'),
(4, 2, N'�����'),
(5, 2, N'����'),
(6, 3, N'������'),
(7, 3, N'����'),
(8, 3, N'�����'),
(9, 3, N'������'),
(10, 4, N'�����');
SET IDENTITY_INSERT [shopping] OFF;