1) statLink = (argc > 1) && strcmp(argv[1], "-l") == 0;
-> argc�� 1���� ũ�� strcmp(argv[1], "-l" )�� ������� 0 �̸� (True)�̸� statLink �� ���� 1�� �����ϰ� �ƴϸ� 0�� ���� 
2) fname = statLink ? 2 : 1;
-> statLink ���� 1�̸� fname�� 2�� �����ϰ�, 0 �̸� fname�� 1�� ����