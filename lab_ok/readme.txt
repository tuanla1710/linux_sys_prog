1) statLink = (argc > 1) && strcmp(argv[1], "-l") == 0;
-> argc가 1보다 크고 strcmp(argv[1], "-l" )의 결과값이 0 이면 (True)이면 statLink 의 값에 1을 대입하고 아니면 0을 대입 
2) fname = statLink ? 2 : 1;
-> statLink 값이 1이면 fname에 2를 대입하고, 0 이면 fname에 1을 대입