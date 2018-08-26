class Attendance < ApplicationRecord
  belongs_to :user, :required => false
  belongs_to :responsibility
  has_one :seminar, through: :responsibility

  validates :user_id, uniqueness: { scope: :responsibility_id }, :allow_nil => true
end
