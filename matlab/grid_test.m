clear all;

K = 2;
L0 = 1;
m = 1;
cd = 2;

step_size = 0.1;
t_end = 25;

size_t = t_end/step_size; 

number_of_points = 16;
number_of_points_side = sqrt(number_of_points);

v = zeros(size_t, number_of_points, 2);
p = zeros(size_t, number_of_points, 2);


z = 1;
h = 1;    
for j = 1:number_of_points
    
    p(1,j,1) = z*L0;
    p(1,j,2) = h*L0;
    
    % Grid border checking, z = x-axis, h = y-axis
    z = z + 1;
    if z == number_of_points_side+1
       z = 1; 
       h = h + 1;
    end
end

i = 2;
for t = step_size:step_size:t_end
   
    z = 1;
    h = 1;
    for j = 1:number_of_points  
        
        if( (z == 1 || z == number_of_points_side) && h == 1)            
            a = zeros(1,1,2);
            v(i,j,:) = v(i-1,j,:) + a*step_size;
            p(i,j,:) = p(i-1,j,:) + v(i,j,:)*step_size;  
        else
            F_spring_tot = zeros(1,1,2);   

            if(z ~= 1)
                q = p(i-1, j-1, :); % Point to the left
                F_spring_tot = F_spring_tot + calculate_spring_force(p(i-1,j,:), q, K, L0);
            end
            if(z ~= number_of_points_side)
                q = p(i-1, j+1, :); % Point to the right
                F_spring_tot = F_spring_tot + calculate_spring_force(p(i-1,j,:), q, K, L0);
            end

            if(h ~= 1)
                q = p(i-1, j-number_of_points_side, :); % Point above
                F_spring_tot = F_spring_tot + calculate_spring_force(p(i-1,j,:), q, K, L0);
            end
            if(h ~= number_of_points_side)
                q = p(i-1, j+number_of_points_side, :); % Point under
                F_spring_tot = F_spring_tot + calculate_spring_force(p(i-1,j,:), q, K, L0);
            end

            % Calculate Fmg and Fdamp 
            g = zeros(1,1,2);
            g(1,1,1) = -1;
            g(1,1,2) = -9.82;
            
            Fdamp = zeros(1,1,2);
            Fdamp(1,1,:) = -cd*v(i-1,j,:);
            
            Ftot = F_spring_tot + m*g + Fdamp; % + rest of the forces
            a = Ftot/m;
            % Perform numerical method and insert into v and p
            v(i,j,:) = v(i-1,j,:) + a*step_size;
            p(i,j,:) = p(i-1,j,:) + v(i,j,:)*step_size;  
        end
        
        % Grid border checking, z = x-axis, h = y-axis
        z = z + 1;
        if z == number_of_points_side+1
           z = 1; 
           h = h + 1;
        end
    end

    i = i +1;
end

disp("STOP");
