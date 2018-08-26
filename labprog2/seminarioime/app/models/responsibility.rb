class Responsibility < ApplicationRecord
  belongs_to :user
  belongs_to :seminar
  has_many :attendances

  validates :user_id, uniqueness: { scope: :seminar_id }
end
