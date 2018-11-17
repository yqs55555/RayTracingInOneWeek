#pragma once

#include "Hitable.h"
namespace YQS
{
	//�洢�����е����й�����ײ��
	class Hitable_list : public Hitable
	{
	public:
		Hitable_list(Hitable ** list, int size)
			:list(list), list_size(size)
		{
			
		}
		//ray:���� t_min:���������ײ���� t_max������Զ��ײ���� rec������ײ���ĵ�һ������ 
		bool hit(const Ray& ray, float t_min, float t_max, Hit_record& rec) const override
		{
			Hit_record temp_rec;
			bool hit_anything = false;
			float closest_so_far = t_max;		//����������ײ�������������
			for(int i = 0;i < list_size;i++)	//���������е���������
			{
				if(list[i]->hit(ray, t_min, closest_so_far, temp_rec))	//����������������ray��·���ϣ�ray�ĳ���Ϊt_min~closest_so_far��
				{
					hit_anything = true;			//������ײ
					closest_so_far = temp_rec.t;	//����ray����Զ��ײ����
					rec = temp_rec;					//����recΪ������ײ���ĵ�һ������
				}
			}
			return hit_anything;	
		}
		Hitable** list;
		int list_size;
	};
}