class Interest < ApplicationRecord
    
    belongs_to :user
    belongs_to :seminar
    
    validates :user_id, uniqueness: { scope: :seminar_id }
end
