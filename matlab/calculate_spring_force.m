function [F] = calculate_spring_force(p, q, K, L0)

% p is a 1x1x2
% q is a 1x1x2

p_x = p(1,1,1);
p_y = p(1,1,2);
q_x = q(1,1,1);
q_y = q(1,1,2);

F = zeros(1,1,2);

if(p_x ~= q_x)
    F(1,1,1) = K*(L0 - abs(p_x-q_x))*((p_x-q_x)/abs(p_x-q_x));
end
if(p_y ~= q_y)
    F(1,1,2) = K*(L0 - abs(p_y-q_y))*((p_y-q_y)/abs(p_y-q_y));
end

end

